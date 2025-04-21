#ifndef DATA_CONSTANT_H_
#define DATA_CONSTANT_H_

#include "Assets.h"

#include <gslib.h>
#include <string>

//-------------------------------------------------------ソルジャー-------------------------------------------------

//ソルジャー名前・タグ
const std::string st_Soldier = "Soldier";

//ソルジャーの回転
const GSvector3 SoldierPos{ -5.0f,-6.0f,30.0f };
const GSvector3 SoldierPos2{ 0.0f,-6.0f,30.0f };
const GSvector3 SoldierPos3{ 5.0f,-6.0f,30.0f };
const GSvector3 SoldierPos4{ 2.5f,-6.0f,20.0f };
const GSvector3 SoldierPos5{ -2.5f,-6.0f,20.0f };


//ソルジャーの高さ
const float SoldierHeight{ 0.8f };
//衝突判定の半径
const float SoldierRadius{ 0.5f };
//ヒット位置
const float SoldierHitPosition{ 30.0f };
//攻撃の種類
const int SoldierAttackType{ 1 };

//ソルジャーHP
const int SoldierHealth{ 150 };
//ソルジャースピード
const float SoldierRunSpeed{ 0.02f };
//ソルジャーの攻撃力
const int SoldierNormalDamage{ 3 };
const int SoldierStrongDamage{ 6 };
//ソルジャーのHPオフセット
const GSvector3 SoldierOffset{ 0.5f,2.0f,0.0f };
const GSvector2 SoldierHPValue{ 0.7f,10.0f };

//--------------------------------------------------------ゴーレム---------------------------------------------------

//ゴーレム名前・タグ
const std::string st_Golem = "Golem";
//ゴーレムの高さ
const float GolemHeight{ 1.0f };
//衝突判定の半径
const float GolemRadius{ 0.7f };

const GSvector3 GolemPos{ 0.0f,-10.0f,80.0f };
//HPスライダー
const GSvector2 HPSliderPos{ 330.0f,800.0f };
const GSvector2 HPSliderScale{ 1120.0f,15.0f };
const GScolor HPSliderColor{ 1.0f,0.0f,0.0f,1.0f };
//SPスライダー
const GSvector2 SPSliderPos{ 330.0f,830.0f };
const GSvector2 SPSliderScale{ 1120.0f,15.0f };
const GScolor SPSliderColor{ 1.0f,1.0f,0.0f,1.0f };
//アニメーションスピード
const float GolemAnimSpeed{ 0.5f };
//ヘルス
const int GolemHealth{ 1000 };
//Sp
const int GolemStanPoint{ 100 };
//スピード
const float GolemRunSpeed{ 0.085f };
//ダメージ量
const int GolemNormalDamage{ 8 };
const int GolemStrongDamage{ 10 };
//攻撃を受けた数
const int HitNum{ 4 };

//------------------------------------------------------プレイヤー---------------------------------------------------

//プレイヤー名前・タグ
const std::string st_PlayerTag = "PlayerTag";
const std::string st_Player = "Player";
//攻撃コライダー
const std::string st_PlayerAttackTag = "PlayerAttackCollider";
//通常攻撃
const std::string st_PlayerNormalAttack = "PlayerNormalAttack";
//強い攻撃
const std::string st_PlayerStrongAttack = "PlayerStrongAttack";
//怯み攻撃
const std::string st_PlayerBlowAttack = "PlayerBlowOffAttack";
//吹き飛ばす攻撃
const std::string st_PlayerPushUpAttack = "PlayerPushUpAttack";
//波動攻撃
const std::string st_PlayerWaveAttack = "PlayerWaveAttack";


//プレイヤーの位置
const GSvector3 PlayerPos{ 0.0f,-6.0f,15.0f };
const GSvector3 TitlePlayerPos{ 1.0f,-1.65f,5.0f };

//自分の高さ
const float PlayerHeight{ 0.8f };
//衝突判定の半径
const float PlayerRadius{ 0.5f };

//通常リムカラー
const GScolor usually_color{ 1.0f,1.0f,1.0f,1.0f };
const float  usually_exponent{ 7.0f };
//ジャスト回避リムカラー
const GScolor just_avoidance_color{ 0.0f,0.088f,1.0f,1.0f };
const float  avoid_exponent{ 6.0f };
//ヒールカラー
const GScolor heal_color{ 0.0f,1.0f,0.6f,1.0f };
const float  heal_exponent{ 3.0f };
//パワーアップカラー
const GScolor power_color{ 1.0f,0.6f,0.0f,1.0f };
const float  power_exponent{ 3.0f };
//HPスライダー描画
const GSvector2 PlayerHPSliderPos{ 30.0f,110.0f };
//HPスライダーの大きさ
const GSvector2 PlayerHPSliderScale{ 5.0f,15.0f };
//HPスライダーのカラー
const GScolor PlayerHPSliderColor{ 0.0f,1.0f,0.0f,1.0f };

//ウェポンの位置
const GLfloat RotateWeaponX{ 73.0f };
const GLfloat RotateWeaponY{ -64.0f };
const GLfloat RotateWeaponZ{ -19.0f };
//プレイヤーボーンの位置
const int PlayerBoneNum{ 25 };
//ボタン位置
const GSvector2 XButtonPos{ 500.0f,500.0f };
const GSvector2 XButtonSc{ 0.2f,0.2f };

//回転速度
const float RotateSpeed{ 20.0f };

//ボス戦に入れる座標
const float BossFightPos{ 60.0f };

//スロー状態の倍率
const float SlowMagnificationValue{ 0.3f };

//スロー状態の倍率
const float PlayerHitStopTime{ 8.0f };

//コライダ―補正値
const float WaveVelocityOffset{ 0.5f };

//ヒット角度(前方向)
const float HitForwardAngle{ 30.0f };
//ヒット角度(後ろ方向)
const float HitBackwardAngle{ 150.0f };

//---------------------------------------------------------プレイヤーステータス----------------------------------------

//体力
const int	DefaultHealth{ 150 };
//体力回復量
const int DefaultHealPowerHealth{ 1 };
// 移動速度
const float DefaultWalkSpeed{ 0.13f };
//基礎攻撃力
const float DefaultBasicAttackPower{ 30.0f };
//基礎スタン量
const float DefaultBasicStanPower{ 7.0f };
//スキル使用していなかったら
const float DefaultAttackPower{ 1.0f };
//無敵時間
const float DefaultInvincibleTime{ 8.0f };
//回避距離
const float DefaultAvoidDistance{ 0.2f };
//フルチャージを行う体力割合
const float FullChargeInvokerate{ 1.0f };
//フルチャージの時の攻撃倍率
const float FullChargePowerUpValue{ 1.5f };
//火事場が発動する体力の割合
const float CrisisChargeInvokeRate{ 0.2f };
//火事場の攻撃上昇倍率
const float CrisisChargePowerUpValue{ 2.0f };

//攻撃倍率設定
const float NormalAttackMultiplier1{ 0.8f };			//通常攻撃1
const float NormalAttackMultiplier2{ 1.0f };			//通常攻撃2
const float NormalAttackMultiplier3{ 2.2f };			//通常攻撃3
const float CounterAttackMultiplier{ 1.5f };			//カウンター攻撃
const float BlowAttackMultiplier{ 1.5f };				//ブロウ攻撃1
const float BlowReinforcementAttackMultiplier1{ 4.0f };	//ブロウ攻撃2
const float PushUpAttackMultiplier{ 3.0f };				//プッシュ攻撃
const float AvoidAttackMultiplier{ 2.0f };				//回避攻撃
const float RotatingNormalAttackMultiplier{ 1.5f };		//回転斬り
const float InpactAttackMultiplier{ 1.8f };				//インパクト攻撃1
const float InpactAttackMultiplier2{ 2.5f };			//インパクト攻撃2
const float SlamAttackMultiplier{ 1.5f };				//スラム攻撃1
const float SlamAttackMultiplier2{ 2.5f };				//スラム攻撃2
const float WildDanceMultiplier{ 0.8f };				//乱舞1
const float WildDanceMultiplier2{ 1.1f };				//乱舞2
const float WildDanceMultiplier3{ 1.3f };				//乱舞3
const float WildDanceMultiplier4{ 1.5f };				//乱舞4
const float WildDanceMultiplier5{ 1.7f };				//乱舞5
const float WildDanceMultiplier6{ 1.9f };				//乱舞6
const float WildDanceMultiplier7{ 2.1f };				//乱舞7
const float WaveWildDanceMultiplier{ 1.2f };			//波動乱舞1
const float WaveWildDanceMultiplier2{ 1.5f };			//波動乱舞2
const float WaveWildDanceMultiplier3{ 2.5f };			//波動乱舞3
const float FangsMultiplier{ 3.5f };					//牙突



//------------------------------------------------------------プレイヤースキルの詳細----------------------------------------

//最大HPアップの倍率
const float HealthUpValue{ 2.0f };
//攻撃力アップ(小)の倍率
const float AttackPowerUpValue{ 5.0f };
//攻撃力(大)の倍率
const float AttackPowerLergeUpValue{ 15.0f };
//ダメージ上昇倍率
const float DamageIncreaseMultiplier{ 1.5 };
//体力回復量の倍率
const float HealthHealPowerUpValue{ 2.0f };
//回避距離上昇値
const float AvoidDistance{ 1.5f };
//無敵時間上昇量
const float InvincibleTime{ 30.0f };
//体力最大時の攻撃力上昇倍率
const float FullChargePowerupValue{ 2.0f };
//火事場状態の倍率
const float CrisisChargerPowerUpValue{ 2.5f };
//スピード減少倍率
const float DecreaseMoveSpeed{ 0.8f };

//--------------------------------------------------------プレイヤーアイテム-----------------------------------------------

//体力回復量
const int ItemHealthValue{ 30 };
//攻撃力アップの倍率
const float ItemAttackPowerUpValue{ 1.2f };
//攻撃力上昇時間
const float ItemAttackPowerUpTime{ 60.0f * 30.0f };

//---------------------------------------------------------画面の描画-----------------------------------------------------

//スキル描画の位置
const GSvector2 SkillDrawPos{ 10.0f,20.0f };
//スキル描画の大きさ
const GSvector2 SkillScale{ 0.3f,0.3f };
//位置を変える
const float SkillPosShift{ 70.0f };
//アイテムアイコンの位置補正
const GSvector2 IconDifference{ 350.0f,150.0f };
//アイコン位置の設定
const GSvector2 IconPosition = GSvector2{ ScreenWidth,ScreenHeight } - IconDifference;
//攻撃アイコンの計算
const GSvector2 AttackIconPos = IconPosition - GSvector2{ 50.0f,150.0f };
//回避アイコンの計算
const GSvector2 AvoidIconPos = IconPosition - GSvector2{ -60.0f,80.0f };
//アイテム・アビリティアイコン
const GSvector2 ItemAndAbilityIconPos = IconPosition - GSvector2{ -210.0f,110.0f };

//アイテム・アビリティアイコンの大きさ
const GSvector2 ItemAndAbilityIconScale{ 0.2f,0.2f };
// アイコンの大きさ
const GSvector2 IconScale{ 0.5f,0.5f };
//説明描画
const GSvector2 OperationExplanationScale{ 0.7f,0.7f };
//操作説明アイコン描画
const GSvector2 OperationExplanationPos{ ScreenWidth - 380.0f,150.0f };
//背景アイコン表示の描画
const GSvector2 BackIconPos{ -170.0f,150.0f };
//背景アイコンをずらす位置
const GSvector2 IconShiftPos{ 110.0f,80.0f };

//背景アイコンの数
const int IconNum{ 2 };

//---------------------------------------------------------ドア--------------------------------------------------------

//位置
const GSvector3 DoorPos{ -1.7f,-6.6f,40.0f };
//
const float DoorColorTime{ 0.01f };

//ドア名前・タグ
const std::string st_DoorTag = "DoorTag";
const std::string st_Door = "Door";


//-----------------------------------------------------カメラ-----------------------------------------------

//デフォルトカメラ
const GSvector3 DefaultCameraPos{ 0.0f,-4.0f,10.0f };
const GSvector3 DefaultCameraAt{ 0.0f,1.0f,0.0f };
//タイトルカメラ
const GSvector3 TitleCameraPos{ 0.0f,-4.18f,25.8f };
const GSvector3 TitleCameraAt{ 0.0f,-3.1f,10.f };
//選択カメラ
const GSvector3 SetCameraPos{ -0.3f,-1.1f,1.0f };
const GSvector3 SetCameraAt{ -0.3f,-0.9f,18.0f };

//カメラ名前・タグ
const std::string st_CameraTag = "CameraTag";
const std::string st_Camera = "Camera";
//カメラシェイクの時間
const float ShakeTime{ 10.0f };
const float RandomShakeRange{ 0.1f };

//カメラの移動範囲
const float RangeX{ -55.0f };
const float RangeY{ 25.0f };
//補正値
const GSvector3 PlayerOffset{ 0.0f,1.5f,-5.0f };
const GSvector3 ReferencePointOffset{ 0.0f,1.7f,0.0f };
const float Radius{ 5.0f };

//補間
const float SmoothTime{ 12.0f };//補間フレーム数
const float MaxSpeed{ 1.0f };	//移動スピードの最大値

//カメラのエフェクトのカラー定数
const GScolor CameraEffectColor{ 1.0f,1.0f,1.0f,0.2f };

//----------------------------------------------------ターゲット-------------------------------------------

//ターゲット名前・タグ
const std::string st_TargetTag = "TargetTag";
const std::string st_Target = "Target";

//寿命
const float TargetLifeSpan{ 30.0f };
//補正値
const float TargetOffset{ 0.5f };
//ターゲット画像のセンター
const GSvector2 TargetCenter{ 128.0f,128.0f };

//----------------------------------------------------チケット-----------------------------------------

//チケット名前・タグ
const std::string  st_TicketTag = "TicketTag";
const std::string  st_Ticket = "Ticket";


//---------------------------------------------------コライダ―----------------------------------------

//コライダー名前・タグ
const std::string st_AvoidTag = "AvoidColliderTag";
const std::string st_Avoid = "AvoidCollider";

//------------------------------------------------------ライト-------------------------------------------

//ライト名前・タグ
const std::string st_Light = "Light";
const std::string st_LightTag = "LightTag";

const float Ambient[4] = { 0.0f,0.0f,0.0f,0.0f };
const float Diffuse[4] = { 0.0f,0.0f,0.0f,1.0f };
const float Specular[4] = { 1.0f,1.0f,1.0f,1.0f };
const float Position[4] = { 100.0f,100.0f,100.0f,0.0 };
//減衰パラメータ
const float LightConstantAttenuation{ 1.0f };
const float LightLinearAttenuation{ 0.0f };
const float LightQuadtaticAttenuation{ 0.07f };
//フォグ
const float FogColor[4]{ 1.0f,0.946f,0.382f,1.0f };
const float FogStart{ 1.0f };
const float FogEnd{ 244.0f };

//------------------------------------------------------共通----------------------------------------------------------

//敵の名前
const std::string st_Enemy = "EnemyTag";
//敵の攻撃
const std::string st_EnemyAttackTag = "EnemyAttackTag";
const std::string st_EnemyAttack = "EnemyAttack";
const std::string st_EnemyStrongAttack = "EnemyStrongAttack";


//敵の出現時の回転の計算
const GSvector3 EnemyRotate{ 0.0f,180.0f,0.0f };
//敵のHpカラー
const GScolor EnemyHPColor{ 1.0f,0.1f,0.1f,1.0f };


// 乗算カラー用(glColor)
const GScolor MultiplicationColor{ 1.0f, 1.0f, 1.0f, 1.0f };
//出現カラー
const float GenerateTime{ 0.01f };
//攻撃時のリムカラー
const GScolor AttackColor{ 1.0f, 0.0f, 0.0f, 1.0f };
const float  AttackExponent{ 2.0f };
// フラッシュカラー
const GScolor m_FlashColor{ 1.0f, 1.0f, 0.5f, 1.0f };
//揺らす値
const float ElasticValue{ -0.2f };
//ヒットストップタイマー
const float HitStopTime{ 10.0f };
//ヒットストップタイマー
const float ExtictionTime{ 0.1f };
//攻撃ディレイ
const float AttackDelay{ 10.0f };

//足元のオフセット
const float FootOffset{ -0.1f };
//重力
const float Gravity{ -0.09f };
//視界確認の値
const float TargerAngleValue{ 10.0f };
//スロー倍率
const float SlowMagnification{ 0.1f };
//移動量倍率
const float OverlapValue{ 0.5f };

//-----------------------------------------------------メッセージ-------------------------------------------------

//扉がなくなる際のメッセージ
const std::string st_Message_Die = "Die";
//扉が開く際のメッセージ
const std::string st_Message_IsOpen = "IsOpen";
//ヒット時のメッセージ
const std::string st_Message_Hit = "Hit";
////扉が開く際カメラ側のメッセージ
const std::string st_Message_OpenDoor = "OpenDoor";
//現在ターゲットにしている敵の確認メッセージ
const std::string st_Message_Target = "Target";
//セレクトシーン確認のメッセージ
const std::string st_Message_SelectScene = "IsSelectScene";


#endif