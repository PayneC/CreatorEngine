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

	unsigned char header[8];				//pngǰ8���ֽڣ���ʶ�Ƿ�Ϊpng�ļ���1-8�� 

	png_byte bit_depth;						//25�ֽ����(ɫ��)
	png_byte color_type;					//26��ɫ����
	int number_of_passes;					//29����ɨ��

	png_structp png_ptr;					//ͼƬ
	png_infop info_ptr;						//ͼƬ����Ϣ

	png_bytepp row_pointers;				//����ָ�� ÿ��ָ�� ָ��һ������
	GLubyte	*rgba;							//������Ҫ������ֵ����

	int row, col, pos, k;					//��������ʱ��

	//��ֻ����ʽ���ļ���Ϊfile_name���ļ�
	FILE *fp = fopen(filename, "rb");
	if (!fp)
	{
		fclose(fp);	//�رմ򿪵��ļ���
		return 0;	//�˴�Ӧ�õ���һ������Ĭ����ͼ����ID�ĺ���(����)
	}

	//��ȡ�ļ�ͷ�ж��Ƿ���pngͼƬ.������������Ӧ����
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8))
	{
		fclose(fp);
		return 0;
	}

	//����libpng��libpng-manual.txt��˵��ʹ���ĵ� �����������ʼ��png_structp �� png_infop

	//�������ǰ󶨴����Լ�����ĺ�����������Ϊ��
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		fclose(fp);
		return 0;
	}

	//���ݳ�ʼ����png_ptr��ʼ��png_infop
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		//��ʼ��ʧ���Ժ�����png_structp
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		//����png_structp
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}					

	//����Ҫȷ����ͨ��2���ƴ򿪵��ļ�
	//ͨ��i/o���ƺ���png_init_io
	png_init_io(png_ptr, fp);
	//�ƺ���˵Ҫ����libpng�ļ��ӵڼ�����ʼmissing
	png_set_sig_bytes(png_ptr, 8);
	//�����ֻ��򵥵Ĳ��������ڿ���ʵ�ʶ�ȡͼƬ��Ϣ�ˣ�
	png_read_info(png_ptr, info_ptr);
	//���ͼƬ����Ϣ width height ��ɫ����  �ֽ����
	pChunk->m_dWidth = png_get_image_width(png_ptr, info_ptr);//17-20
	pChunk->m_dHeight = png_get_image_height(png_ptr, info_ptr);//21-24
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	//���ͼƬ����alphaͨ������Ҫ
	if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
	{
		png_set_swap_alpha(png_ptr);
	}
	//����ɨ��ͼƬ  �������Ҫ���ò��ܽ���
	number_of_passes = png_set_interlace_handling(png_ptr);
	//����ȡ������Ϣ���µ�info_ptr
	png_read_update_info(png_ptr, info_ptr);

	//���ļ�
	if (setjmp(png_jmpbuf(png_ptr))){
		fclose(fp);
		return 0;
	}

	//����png ������������ ��-��-�Ӷ�����
	//����ͼ��Ҫ�����ض��� ��-��-�׵���
	//������������Ҫ���������ݽ���һ����������

	//�����洢 png ����ֵ������
	row_pointers = (png_bytep*)malloc(sizeof(png_bytep)* pChunk->m_dWidth);

	//��row_pointers����ת����������
	rgba = (GLubyte*)malloc(pChunk->m_dWidth * pChunk->m_dHeight * 4);

	for (k = 0; k < pChunk->m_dHeight; k++)
		row_pointers[k] = NULL;

	//ͨ��ɨ���������ÿһ�н��õ������ݸ�ֵ����̬����
	//��ÿ��ָ�� ����һ���ռ䣨�У�
	for (k = 0; k < pChunk->m_dHeight; k++)
	{
		row_pointers[k] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));
	}

	//��ͼƬ
	png_read_image(png_ptr, row_pointers);
	//����ǰλ�� ƫ�Ƶ� ���� ��
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

	//����������ͼ��Ч
	glEnable(GL_TEXTURE_2D);

	//��������ID��û���õ� �����ﷵ��һ������ID
	glGenTextures(1, &pChunk->m_dTextureId);

	//������󶨵�ID
	glBindTexture(GL_TEXTURE_2D, pChunk->m_dTextureId);

	//������ͼ������Ļ��Ч��������Ĭ��ֻ������
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//�����������õ�ͼƬ����
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pChunk->m_dWidth, pChunk->m_dHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);

	for (k = 0; k < pChunk->m_dHeight; k++)
	{
		free(row_pointers[k]);
	}
	free(row_pointers);

	fclose(fp);

	return pChunk;
}