#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

class NumberTexture {
public:

	//�R���X�g���N�^
	NumberTexture(GSuint texture, int width, int height);
	//�`��(�E�l��)
	void Draw(const GSvector2& position, int num, int digit, char fill = '0')const;
	//�`��(���l��)
	void Draw(const GSvector2& position, int num)const;
	//�`��
	void Draw(const GSvector2& position, const std::string& num)const;

private:

	//�t�H���g�p�̃e�N�X�`��
	GSuint m_Texture;
	//��
	int m_Width;
	//����
	int m_Height;
};


#endif