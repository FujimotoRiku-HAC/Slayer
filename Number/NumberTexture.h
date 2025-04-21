#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

class NumberTexture {
public:

	//コンストラクタ
	NumberTexture(GSuint texture, int width, int height);
	//描画(右詰め)
	void Draw(const GSvector2& position, int num, int digit, char fill = '0')const;
	//描画(左詰め)
	void Draw(const GSvector2& position, int num)const;
	//描画
	void Draw(const GSvector2& position, const std::string& num)const;

private:

	//フォント用のテクスチャ
	GSuint m_Texture;
	//幅
	int m_Width;
	//高さ
	int m_Height;
};


#endif