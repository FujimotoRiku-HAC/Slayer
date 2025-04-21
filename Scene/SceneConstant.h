#ifndef SCENE_CONSTANT_H_
#define SCENE_CONSTANT_H_

#include <gslib.h>
#include "Assets.h"
//------------------------------------------------------EditScene------------------------------------------------

// 選択カーソル位置
const GSvector2 EditRectPos{ 90,170 };
//アビリティTextの位置
const GSvector2 AbilityTextNamePos{ 100,400 };
//Text切り取りの大きさ
const GSvector2 EditRectScale{ 500,50 };
//アビリティフレームのポジション
const GSvector2 AbilityBackFramePos{ 75.0f,450.0f };
//アビリティ選択フレーム位置
const GSvector2 AbilityFramePos{ 70.0f,454.0f };
//アビリティ位置
const GSvector2 AbilityPos{5.9f,4.2f};

//フレーム切り取りの大きさ
const GSvector2 FrameRectPos{ 330.0f,30.0f };

//スキルフレームのポジション
const GSvector2 SkillBackFramePos{ 75.0f,520.0f };
//スキル選択フレーム位置
const GSvector2 SkillFramePos{ 70.0f,524.0f };
//スキルの位置
const GSvector2 SkillPos{ 7.0f,2.0f };
//スキルTextの位置
const GSvector2 SkillTextNamePos{ 100,480 };
//スキルの大きさ
const GSvector2 TextNameScale{ 0.6f,1.0f };


//ボックスの大きさ
const GSvector2 BoxScale{ 0.4f,0.4f };
//バックグラウンドの大きさ
const GSvector2 FrameScale{ 0.71f,0.5f };
//スロットの大きさ
const GSvector2 SlotScale{ 0.25f,0.25f };
//持ち物の大きさ
const GSvector2 TextScale{ 0.2f,0.2f };
//バックの大きさ
const GSvector2 BackGroundScale{ 1.4f,1.55f };
//スクロールバーの大きさ
const GSvector2 ScrollScale{ 1.53f,1.2f };
//スクロールバー切り取り
const float ScrollBarRect{ 256.0f };
//アビリティスクロールバー
const GSvector2 AbilityScrollBarScaleRect{ 15.0f,75.0f };
//スキルスクロールバー
const GSvector2 SkillScrollBarScaleRect{ 15.0f,100.0f };

// 説明描画位置
const GSvector2 ExplanationRect{ 1250,300 };
//説明描画の大きさ
const GSvector2 ExplanationScale{ 0.7f,0.7f };
//ボックス切り取りの大きさ
const GSvector2 BoxRectScale{ 50.0f,160.0f };
//ボックス位置
const GSvector2 SlotPos{ 10.0f,100.0f};

//リターンの位置
const GSvector2 ReturnPos{ 30.0f,ScreenHeight - 150.0f };
// 空白の大きさ
const float BlankScale{ 5 };
const float AbilityBlankScale{ 150 };
const float SkillBlankScale{ 50 };

// 一度に表示する選択肢の数
const int FieldListNum{ 6 };
// テクスチャのセットアイテム切り取り
const GSvector2 TextureOfSkillField{ 500,700 };
// テクスチャのセットスキル切り取り
const GSvector2 TextureOfAbilityField{ 0,50 };

//-----------------------------------------エディットシーン--------------------------------

//枠
const GSrect EditFrameRect{ -1.0f, 90.0f , 300.0f , 150.0f };

const GSvector2 EditTextPos{ 10.0f,100.0f };

const GScolor EditTextColor{ 1.0f,1.0f,1.0f,1.0f };

const GSrect EditRect{ 0.0f,0.0f,400.0f,50.0f };

const float EditDrawShift{ 75.0f };

const int EditTextNum{ 4 };

const float RectShiftPos{ 75.0f };

//----------------------------------------------------------TitleScene-------------------------------------------

//Text切り取りの大きさ
const GSvector2 TitleRectScale{ 400,50 };
//空白
const float TitleTextBlankScale{ 75.0f };
//テキスト欄の数
const int TitleTextFieldNum{ 3 };

const GSvector2 TitleTextPosSet{ 130.0f,180.0f };

//----------------------------------------------------------OptionScene-------------------------------------------

//テキスト欄の数
const int OptionTextFieldNum{ 2 };
//オプションテキストの切り取りの大きさ
const GSvector2 OptionTextScale{ 500.0f,45.0f };
//リターンの位置
const GSvector2 OptionReturnScale{ 860.0f,570.0f };
//テキストの位置
const GSvector2 OptionTextPos{ 10.0f,200.0f };
//空白
const float OptionBlankScale{ 140.0f };
//スライダー
const float OptionSliderValue{ 0.1f };

//BGM位置
const GSrect OptionBGMRect{ 10,200,150,250 };
//SE位置
const GSrect OptionSERect{ 10,340,150,390 };
//リターン位置
const GSrect OptionReturnRect{ 850,570,1100,620 };

//BGM
const GSvector2 BGMSliderPos{ 200.0f,215.0f };
const GSvector2 BGMSliderValue{ 400.0f,25.0f };
const GScolor BGMSliderColor{ 0.0f,1.0f,0.0f,1.0f };

//SE
const GSvector2 SESliderPos{ 200.0f,360.0f };
const GSvector2 SESliderValue{ 400.0f,25.0f };
const GScolor SESliderColor{ 0.0f,1.0f,0.0f,1.0f };


//---------------------------------------------------------LoadScene-----------------------------------------------

//ロードテキスト描画
const GSvector2 LoadTextPos{ ScreenWidth - 150.0f,ScreenHeight - 150.0f };
const GSvector2 NowLoadTextPos{ ScreenWidth / 2 - 250.0f,ScreenHeight / 2 - 100.0f };

//ＮＯＷロードテキスト
const GSvector2 LoadCenterPos{ 64.0f,64.0f };

//---------------------------------------------------------ゲームプレイシーン--------------------------------

//テキストの数
const int ClearFirstTextNum{ 1 };

const int ClearTextNum{ 3 };
//位置の補正値
const float ClearTextPosOffset{ 190.0f };

const GSvector2 ClearTextShiftPosOffset{ 35.0f,75.0f };


//----------------------------------------------------------ClearScene--------------------------------------------

//クリアシーンの切り取り
const GSvector2 ClearRectScale{ 500.0f,45.0f };
//
const GSvector2 SceneName{ 10.0f,20.0f };

//ランクのポジション
const GSvector2 ClearRankPos{ 100.0f,180.0f };
const GSvector2 RankPos{ 280.0f,205.0f };
const GSvector2 ClearScale{ 1.2f,1.0f };
const GSvector2 RankScale{ 1.5f,1.5f };
const GSvector2 RankRectScale{ 300.0f,45.0f };
//ランクタイム
const float ARankTime{ 60.0f };
const float BRankTime{ 120.0f };
const float CRankTime{ 180.0f };
//クリアシーンバックグラウンド
const GSrect ClearRectBG{ 100.0f,180.0f,ScreenWidth - 100.0f,ScreenHeight - 180.0f };
//クリア表示
const GSvector2 ClearPos{ ScreenWidth / 2 - 200.0f, ScreenHeight / 2 - 200.0f };
//
const GSvector2 ClearTextPos{ 110.0f,180.0f };

//----------------------------------------------------------ゲームオーバー----------------------------------

//テキスト切り取り
const GSvector2 GameOverRect{ 500.0f,60.0f };
//ゲームオーバー位置
const GSvector2 OverPos{ 250.0f,200.0f };
//テキスト位置
const GSvector2 OverTextPos{ 250.0f,100.0f };
//位置移動
const float OverTextShiftPos{ 80.0f };
//テキスト数
const int OverTextNum{ 3 };

//----------------------------------------------------共通----------------------------------------

//シャドウマップ
const GSuint ShadowMapSize[] = { 2048,2048 };
//シャドウマップを適用する距離
const float ShadowMapDis{ 60.0f };
//カスケードシャドウマップの分割する距離(デフォルトは0.5)
const float ShadowMapCascade{ 0.7f };
//シャドウの濃さを設定
const float ShadowMapAttenuation{ 0.6f };


// 選択色
const GScolor SelectColor{ 0.0f,1.0f,1.0f,0.5f };

#endif // !EDIT_CONSTANT_H_