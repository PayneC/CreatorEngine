#include "CrTexturePool.h"
#include <libpng\png.h>
#include <fbxsdk.h>

CrTexturePool::CrTexturePool()
{
}

CrTexturePool::~CrTexturePool()
{
}

CrTextureChunk * CrTexturePool::CreateTexture(const char* filename)
{
	std::map<std::string, CrTextureChunk*>::iterator iter = m_mapTexture.find(filename);
	CrTextureChunk * pChunk = NULL;

	if (m_mapTexture.end() == iter)
	{
		pChunk = ReadPng(filename);
		m_mapTexture.insert(std::make_pair(filename, pChunk));
	}
	else
	{
		pChunk = iter->second;
	}

	return pChunk;
}

CrTextureChunk * CrTexturePool::ReadPng(const char* filename)
{
	CrTextureChunk * pChunk = new CrTextureChunk();

	unsigned char header[8];				//png前8个字节，标识是否为png文件（1-8） 

	png_byte bit_depth;						//25字节深度(色深)
	png_byte color_type;					//26颜色类型
	int number_of_passes;					//29隔行扫描

	png_structp png_ptr;					//图片
	png_infop info_ptr;						//图片的信息

	png_bytepp row_pointers;				//二级指针 每个指针 指向一行数据
	GLubyte	*rgba;							//最终需要的像素值数组

	int row, col, pos, k;					//复制像素时用

	//以只读形式打开文件名为file_name的文件
	FILE *fp = fopen(filename, "rb");
	if (!fp)
	{
		fclose(fp);	//关闭打开的文件！
		return 0;	//此处应该调用一个生成默认贴图返回ID的函数(建议)
	}

	//读取文件头判断是否所png图片.不是则做出相应处理
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8))
	{
		fclose(fp);
		return 0;
	}

	//根据libpng的libpng-manual.txt的说明使用文档 接下来必须初始化png_structp 和 png_infop

	//后三个是绑定错误以及警告的函数这里设置为空
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		fclose(fp);
		return 0;
	}

	//根据初始化的png_ptr初始化png_infop
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		//初始化失败以后销毁png_structp
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		//销毁png_structp
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}					

	//你需要确保是通过2进制打开的文件
	//通过i/o定制函数png_init_io
	png_init_io(png_ptr, fp);
	//似乎是说要告诉libpng文件从第几个开始missing
	png_set_sig_bytes(png_ptr, 8);
	//如果你只想简单的操作你现在可以实际读取图片信息了！
	png_read_info(png_ptr, info_ptr);
	//获得图片到信息 width height 颜色类型  字节深度
	pChunk->m_dWidth = png_get_image_width(png_ptr, info_ptr);//17-20
	pChunk->m_dHeight = png_get_image_height(png_ptr, info_ptr);//21-24
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	//如果图片带有alpha通道就需要
	if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
	{
		png_set_swap_alpha(png_ptr);
	}
	//隔行扫描图片  这个必须要调用才能进行
	number_of_passes = png_set_interlace_handling(png_ptr);
	//将读取到的信息更新到info_ptr
	png_read_update_info(png_ptr, info_ptr);

	//读文件
	if (setjmp(png_jmpbuf(png_ptr))){
		fclose(fp);
		return 0;
	}

	//由于png 他的像素是由 左-右-从顶到底
	//而贴图需要的像素都是 左-右-底到顶
	//所以在这里需要把像素内容进行一个从新排列

	//创建存储 png 像素值的数组
	row_pointers = (png_bytep*)malloc(sizeof(png_bytep)* pChunk->m_dWidth);

	//从row_pointers最终转换到的数组
	rgba = (GLubyte*)malloc(pChunk->m_dWidth * pChunk->m_dHeight * 4);

	for (k = 0; k < pChunk->m_dHeight; k++)
		row_pointers[k] = NULL;

	//通过扫描流里面的每一行将得到的数据赋值给动态数组
	//给每个指针 赋予一个空间（行）
	for (k = 0; k < pChunk->m_dHeight; k++)
	{
		row_pointers[k] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));
	}

	//读图片
	png_read_image(png_ptr, row_pointers);
	//将当前位置 偏移到 左下 角
	pos = (pChunk->m_dWidth * pChunk->m_dHeight * 4) - (4 * pChunk->m_dWidth);

	for (row = 0; row < pChunk->m_dHeight; row++)
	{
		for (col = 0; col < (4 * pChunk->m_dWidth); col += 4)
		{
			rgba[pos++] = row_pointers[row][col];        // red
			rgba[pos++] = row_pointers[row][col + 1];    // green
			rgba[pos++] = row_pointers[row][col + 2];    // blue
			rgba[pos++] = row_pointers[row][col + 3];    // alpha
		}
		pos = (pos - (pChunk->m_dWidth * 4) * 2);
	}

	//开启纹理贴图特效
	glEnable(GL_TEXTURE_2D);

	//创建纹理ID从没有用到 整数里返回一个整数ID
	glGenTextures(1, &pChunk->m_dTextureId);

	//将纹理绑定到ID
	glBindTexture(GL_TEXTURE_2D, pChunk->m_dTextureId);

	//设置贴图和纹理的混合效果这里是默认只用纹理
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//设置纹理所用到图片数据
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pChunk->m_dWidth, pChunk->m_dHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);

	for (k = 0; k < pChunk->m_dHeight; k++)
	{
		free(row_pointers[k]);
	}
	free(row_pointers);

	fclose(fp);

	return pChunk;
}