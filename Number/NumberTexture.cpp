#include "NumberTexture.h"

NumberTexture::NumberTexture(GSuint texture, int width, int height):
	m_Texture{ texture }, m_Width{ width }, m_Height{ height } {
}

void NumberTexture::Draw(const GSvector2& position, int num, int digit, char fill)const{
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << num;
	Draw(position, ss.str());
}

void NumberTexture::Draw(const GSvector2& position, int num) const{
	Draw(position, std::to_string(num));
}

void NumberTexture::Draw(const GSvector2& position, const std::string& num) const{
	//1���`��
	for (int i = 0; i < (int)num.size(); ++i) {
		//�󔒂̓X�L�b�v
		if (num[i] == ' ')continue;
		//char�^��int�^�ɕϊ�
		int n = num[i] - '0';
		//�����ɑΉ�����摜��؂�o�����߂̋�`���v�Z����(���l�t�H���g�摜���̈ʒu�j
		GSrect rect(n * m_Width, 0.0f, (n * m_Width) + m_Width, m_Height);
		//������`�悷����W���v�Z
		GSvector2 pos(position.x + i * m_Width, position.y);
		//�������P���`��
		gsDrawSprite2D(m_Texture, &pos, &rect, NULL, NULL, NULL, 0);
	}
}
