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
	//1つずつ描画
	for (int i = 0; i < (int)num.size(); ++i) {
		//空白はスキップ
		if (num[i] == ' ')continue;
		//char型をint型に変換
		int n = num[i] - '0';
		//数字に対応する画像を切り出すための矩形を計算する(数値フォント画像内の位置）
		GSrect rect(n * m_Width, 0.0f, (n * m_Width) + m_Width, m_Height);
		//数字を描画する座標を計算
		GSvector2 pos(position.x + i * m_Width, position.y);
		//数字を１桁描画
		gsDrawSprite2D(m_Texture, &pos, &rect, NULL, NULL, NULL, 0);
	}
}
