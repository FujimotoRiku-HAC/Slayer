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
	//1‚Â‚¸‚Â•`‰æ
	for (int i = 0; i < (int)num.size(); ++i) {
		//‹ó”’‚ÍƒXƒLƒbƒv
		if (num[i] == ' ')continue;
		//charŒ^‚ðintŒ^‚É•ÏŠ·
		int n = num[i] - '0';
		//”Žš‚É‘Î‰ž‚·‚é‰æ‘œ‚ðØ‚èo‚·‚½‚ß‚Ì‹éŒ`‚ðŒvŽZ‚·‚é(”’lƒtƒHƒ“ƒg‰æ‘œ“à‚ÌˆÊ’uj
		GSrect rect(n * m_Width, 0.0f, (n * m_Width) + m_Width, m_Height);
		//”Žš‚ð•`‰æ‚·‚éÀ•W‚ðŒvŽZ
		GSvector2 pos(position.x + i * m_Width, position.y);
		//”Žš‚ð‚PŒ…•`‰æ
		gsDrawSprite2D(m_Texture, &pos, &rect, NULL, NULL, NULL, 0);
	}
}
