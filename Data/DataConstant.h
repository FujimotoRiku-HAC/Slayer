#ifndef DATA_CONSTANT_H_
#define DATA_CONSTANT_H_

#include "Assets.h"

#include <gslib.h>
#include <string>

//-------------------------------------------------------�\���W���[-------------------------------------------------

//�\���W���[���O�E�^�O
const std::string st_Soldier = "Soldier";

//�\���W���[�̉�]
const GSvector3 SoldierPos{ -5.0f,-6.0f,30.0f };
const GSvector3 SoldierPos2{ 0.0f,-6.0f,30.0f };
const GSvector3 SoldierPos3{ 5.0f,-6.0f,30.0f };
const GSvector3 SoldierPos4{ 2.5f,-6.0f,20.0f };
const GSvector3 SoldierPos5{ -2.5f,-6.0f,20.0f };


//�\���W���[�̍���
const float SoldierHeight{ 0.8f };
//�Փ˔���̔��a
const float SoldierRadius{ 0.5f };
//�q�b�g�ʒu
const float SoldierHitPosition{ 30.0f };
//�U���̎��
const int SoldierAttackType{ 1 };

//�\���W���[HP
const int SoldierHealth{ 150 };
//�\���W���[�X�s�[�h
const float SoldierRunSpeed{ 0.02f };
//�\���W���[�̍U����
const int SoldierNormalDamage{ 3 };
const int SoldierStrongDamage{ 6 };
//�\���W���[��HP�I�t�Z�b�g
const GSvector3 SoldierOffset{ 0.5f,2.0f,0.0f };
const GSvector2 SoldierHPValue{ 0.7f,10.0f };

//--------------------------------------------------------�S�[����---------------------------------------------------

//�S�[�������O�E�^�O
const std::string st_Golem = "Golem";
//�S�[�����̍���
const float GolemHeight{ 1.0f };
//�Փ˔���̔��a
const float GolemRadius{ 0.7f };

const GSvector3 GolemPos{ 0.0f,-10.0f,80.0f };
//HP�X���C�_�[
const GSvector2 HPSliderPos{ 330.0f,800.0f };
const GSvector2 HPSliderScale{ 1120.0f,15.0f };
const GScolor HPSliderColor{ 1.0f,0.0f,0.0f,1.0f };
//SP�X���C�_�[
const GSvector2 SPSliderPos{ 330.0f,830.0f };
const GSvector2 SPSliderScale{ 1120.0f,15.0f };
const GScolor SPSliderColor{ 1.0f,1.0f,0.0f,1.0f };
//�A�j���[�V�����X�s�[�h
const float GolemAnimSpeed{ 0.5f };
//�w���X
const int GolemHealth{ 1000 };
//Sp
const int GolemStanPoint{ 100 };
//�X�s�[�h
const float GolemRunSpeed{ 0.085f };
//�_���[�W��
const int GolemNormalDamage{ 8 };
const int GolemStrongDamage{ 10 };
//�U�����󂯂���
const int HitNum{ 4 };

//------------------------------------------------------�v���C���[---------------------------------------------------

//�v���C���[���O�E�^�O
const std::string st_PlayerTag = "PlayerTag";
const std::string st_Player = "Player";
//�U���R���C�_�[
const std::string st_PlayerAttackTag = "PlayerAttackCollider";
//�ʏ�U��
const std::string st_PlayerNormalAttack = "PlayerNormalAttack";
//�����U��
const std::string st_PlayerStrongAttack = "PlayerStrongAttack";
//���ݍU��
const std::string st_PlayerBlowAttack = "PlayerBlowOffAttack";
//������΂��U��
const std::string st_PlayerPushUpAttack = "PlayerPushUpAttack";
//�g���U��
const std::string st_PlayerWaveAttack = "PlayerWaveAttack";


//�v���C���[�̈ʒu
const GSvector3 PlayerPos{ 0.0f,-6.0f,15.0f };
const GSvector3 TitlePlayerPos{ 1.0f,-1.65f,5.0f };

//�����̍���
const float PlayerHeight{ 0.8f };
//�Փ˔���̔��a
const float PlayerRadius{ 0.5f };

//�ʏ탊���J���[
const GScolor usually_color{ 1.0f,1.0f,1.0f,1.0f };
const float  usually_exponent{ 7.0f };
//�W���X�g��������J���[
const GScolor just_avoidance_color{ 0.0f,0.088f,1.0f,1.0f };
const float  avoid_exponent{ 6.0f };
//�q�[���J���[
const GScolor heal_color{ 0.0f,1.0f,0.6f,1.0f };
const float  heal_exponent{ 3.0f };
//�p���[�A�b�v�J���[
const GScolor power_color{ 1.0f,0.6f,0.0f,1.0f };
const float  power_exponent{ 3.0f };
//HP�X���C�_�[�`��
const GSvector2 PlayerHPSliderPos{ 30.0f,110.0f };
//HP�X���C�_�[�̑傫��
const GSvector2 PlayerHPSliderScale{ 5.0f,15.0f };
//HP�X���C�_�[�̃J���[
const GScolor PlayerHPSliderColor{ 0.0f,1.0f,0.0f,1.0f };

//�E�F�|���̈ʒu
const GLfloat RotateWeaponX{ 73.0f };
const GLfloat RotateWeaponY{ -64.0f };
const GLfloat RotateWeaponZ{ -19.0f };
//�v���C���[�{�[���̈ʒu
const int PlayerBoneNum{ 25 };
//�{�^���ʒu
const GSvector2 XButtonPos{ 500.0f,500.0f };
const GSvector2 XButtonSc{ 0.2f,0.2f };

//��]���x
const float RotateSpeed{ 20.0f };

//�{�X��ɓ������W
const float BossFightPos{ 60.0f };

//�X���[��Ԃ̔{��
const float SlowMagnificationValue{ 0.3f };

//�X���[��Ԃ̔{��
const float PlayerHitStopTime{ 8.0f };

//�R���C�_�\�␳�l
const float WaveVelocityOffset{ 0.5f };

//�q�b�g�p�x(�O����)
const float HitForwardAngle{ 30.0f };
//�q�b�g�p�x(������)
const float HitBackwardAngle{ 150.0f };

//---------------------------------------------------------�v���C���[�X�e�[�^�X----------------------------------------

//�̗�
const int	DefaultHealth{ 150 };
//�̗͉񕜗�
const int DefaultHealPowerHealth{ 1 };
// �ړ����x
const float DefaultWalkSpeed{ 0.13f };
//��b�U����
const float DefaultBasicAttackPower{ 30.0f };
//��b�X�^����
const float DefaultBasicStanPower{ 7.0f };
//�X�L���g�p���Ă��Ȃ�������
const float DefaultAttackPower{ 1.0f };
//���G����
const float DefaultInvincibleTime{ 8.0f };
//�������
const float DefaultAvoidDistance{ 0.2f };
//�t���`���[�W���s���̗͊���
const float FullChargeInvokerate{ 1.0f };
//�t���`���[�W�̎��̍U���{��
const float FullChargePowerUpValue{ 1.5f };
//�Ύ��ꂪ��������̗͂̊���
const float CrisisChargeInvokeRate{ 0.2f };
//�Ύ���̍U���㏸�{��
const float CrisisChargePowerUpValue{ 2.0f };

//�U���{���ݒ�
const float NormalAttackMultiplier1{ 0.8f };			//�ʏ�U��1
const float NormalAttackMultiplier2{ 1.0f };			//�ʏ�U��2
const float NormalAttackMultiplier3{ 2.2f };			//�ʏ�U��3
const float CounterAttackMultiplier{ 1.5f };			//�J�E���^�[�U��
const float BlowAttackMultiplier{ 1.5f };				//�u���E�U��1
const float BlowReinforcementAttackMultiplier1{ 4.0f };	//�u���E�U��2
const float PushUpAttackMultiplier{ 3.0f };				//�v�b�V���U��
const float AvoidAttackMultiplier{ 2.0f };				//����U��
const float RotatingNormalAttackMultiplier{ 1.5f };		//��]�a��
const float InpactAttackMultiplier{ 1.8f };				//�C���p�N�g�U��1
const float InpactAttackMultiplier2{ 2.5f };			//�C���p�N�g�U��2
const float SlamAttackMultiplier{ 1.5f };				//�X�����U��1
const float SlamAttackMultiplier2{ 2.5f };				//�X�����U��2
const float WildDanceMultiplier{ 0.8f };				//����1
const float WildDanceMultiplier2{ 1.1f };				//����2
const float WildDanceMultiplier3{ 1.3f };				//����3
const float WildDanceMultiplier4{ 1.5f };				//����4
const float WildDanceMultiplier5{ 1.7f };				//����5
const float WildDanceMultiplier6{ 1.9f };				//����6
const float WildDanceMultiplier7{ 2.1f };				//����7
const float WaveWildDanceMultiplier{ 1.2f };			//�g������1
const float WaveWildDanceMultiplier2{ 1.5f };			//�g������2
const float WaveWildDanceMultiplier3{ 2.5f };			//�g������3
const float FangsMultiplier{ 3.5f };					//���



//------------------------------------------------------------�v���C���[�X�L���̏ڍ�----------------------------------------

//�ő�HP�A�b�v�̔{��
const float HealthUpValue{ 2.0f };
//�U���̓A�b�v(��)�̔{��
const float AttackPowerUpValue{ 5.0f };
//�U����(��)�̔{��
const float AttackPowerLergeUpValue{ 15.0f };
//�_���[�W�㏸�{��
const float DamageIncreaseMultiplier{ 1.5 };
//�̗͉񕜗ʂ̔{��
const float HealthHealPowerUpValue{ 2.0f };
//��������㏸�l
const float AvoidDistance{ 1.5f };
//���G���ԏ㏸��
const float InvincibleTime{ 30.0f };
//�̗͍ő厞�̍U���͏㏸�{��
const float FullChargePowerupValue{ 2.0f };
//�Ύ����Ԃ̔{��
const float CrisisChargerPowerUpValue{ 2.5f };
//�X�s�[�h�����{��
const float DecreaseMoveSpeed{ 0.8f };

//--------------------------------------------------------�v���C���[�A�C�e��-----------------------------------------------

//�̗͉񕜗�
const int ItemHealthValue{ 30 };
//�U���̓A�b�v�̔{��
const float ItemAttackPowerUpValue{ 1.2f };
//�U���͏㏸����
const float ItemAttackPowerUpTime{ 60.0f * 30.0f };

//---------------------------------------------------------��ʂ̕`��-----------------------------------------------------

//�X�L���`��̈ʒu
const GSvector2 SkillDrawPos{ 10.0f,20.0f };
//�X�L���`��̑傫��
const GSvector2 SkillScale{ 0.3f,0.3f };
//�ʒu��ς���
const float SkillPosShift{ 70.0f };
//�A�C�e���A�C�R���̈ʒu�␳
const GSvector2 IconDifference{ 350.0f,150.0f };
//�A�C�R���ʒu�̐ݒ�
const GSvector2 IconPosition = GSvector2{ ScreenWidth,ScreenHeight } - IconDifference;
//�U���A�C�R���̌v�Z
const GSvector2 AttackIconPos = IconPosition - GSvector2{ 50.0f,150.0f };
//����A�C�R���̌v�Z
const GSvector2 AvoidIconPos = IconPosition - GSvector2{ -60.0f,80.0f };
//�A�C�e���E�A�r���e�B�A�C�R��
const GSvector2 ItemAndAbilityIconPos = IconPosition - GSvector2{ -210.0f,110.0f };

//�A�C�e���E�A�r���e�B�A�C�R���̑傫��
const GSvector2 ItemAndAbilityIconScale{ 0.2f,0.2f };
// �A�C�R���̑傫��
const GSvector2 IconScale{ 0.5f,0.5f };
//�����`��
const GSvector2 OperationExplanationScale{ 0.7f,0.7f };
//��������A�C�R���`��
const GSvector2 OperationExplanationPos{ ScreenWidth - 380.0f,150.0f };
//�w�i�A�C�R���\���̕`��
const GSvector2 BackIconPos{ -170.0f,150.0f };
//�w�i�A�C�R�������炷�ʒu
const GSvector2 IconShiftPos{ 110.0f,80.0f };

//�w�i�A�C�R���̐�
const int IconNum{ 2 };

//---------------------------------------------------------�h�A--------------------------------------------------------

//�ʒu
const GSvector3 DoorPos{ -1.7f,-6.6f,40.0f };
//
const float DoorColorTime{ 0.01f };

//�h�A���O�E�^�O
const std::string st_DoorTag = "DoorTag";
const std::string st_Door = "Door";


//-----------------------------------------------------�J����-----------------------------------------------

//�f�t�H���g�J����
const GSvector3 DefaultCameraPos{ 0.0f,-4.0f,10.0f };
const GSvector3 DefaultCameraAt{ 0.0f,1.0f,0.0f };
//�^�C�g���J����
const GSvector3 TitleCameraPos{ 0.0f,-4.18f,25.8f };
const GSvector3 TitleCameraAt{ 0.0f,-3.1f,10.f };
//�I���J����
const GSvector3 SetCameraPos{ -0.3f,-1.1f,1.0f };
const GSvector3 SetCameraAt{ -0.3f,-0.9f,18.0f };

//�J�������O�E�^�O
const std::string st_CameraTag = "CameraTag";
const std::string st_Camera = "Camera";
//�J�����V�F�C�N�̎���
const float ShakeTime{ 10.0f };
const float RandomShakeRange{ 0.1f };

//�J�����̈ړ��͈�
const float RangeX{ -55.0f };
const float RangeY{ 25.0f };
//�␳�l
const GSvector3 PlayerOffset{ 0.0f,1.5f,-5.0f };
const GSvector3 ReferencePointOffset{ 0.0f,1.7f,0.0f };
const float Radius{ 5.0f };

//���
const float SmoothTime{ 12.0f };//��ԃt���[����
const float MaxSpeed{ 1.0f };	//�ړ��X�s�[�h�̍ő�l

//�J�����̃G�t�F�N�g�̃J���[�萔
const GScolor CameraEffectColor{ 1.0f,1.0f,1.0f,0.2f };

//----------------------------------------------------�^�[�Q�b�g-------------------------------------------

//�^�[�Q�b�g���O�E�^�O
const std::string st_TargetTag = "TargetTag";
const std::string st_Target = "Target";

//����
const float TargetLifeSpan{ 30.0f };
//�␳�l
const float TargetOffset{ 0.5f };
//�^�[�Q�b�g�摜�̃Z���^�[
const GSvector2 TargetCenter{ 128.0f,128.0f };

//----------------------------------------------------�`�P�b�g-----------------------------------------

//�`�P�b�g���O�E�^�O
const std::string  st_TicketTag = "TicketTag";
const std::string  st_Ticket = "Ticket";


//---------------------------------------------------�R���C�_�\----------------------------------------

//�R���C�_�[���O�E�^�O
const std::string st_AvoidTag = "AvoidColliderTag";
const std::string st_Avoid = "AvoidCollider";

//------------------------------------------------------���C�g-------------------------------------------

//���C�g���O�E�^�O
const std::string st_Light = "Light";
const std::string st_LightTag = "LightTag";

const float Ambient[4] = { 0.0f,0.0f,0.0f,0.0f };
const float Diffuse[4] = { 0.0f,0.0f,0.0f,1.0f };
const float Specular[4] = { 1.0f,1.0f,1.0f,1.0f };
const float Position[4] = { 100.0f,100.0f,100.0f,0.0 };
//�����p�����[�^
const float LightConstantAttenuation{ 1.0f };
const float LightLinearAttenuation{ 0.0f };
const float LightQuadtaticAttenuation{ 0.07f };
//�t�H�O
const float FogColor[4]{ 1.0f,0.946f,0.382f,1.0f };
const float FogStart{ 1.0f };
const float FogEnd{ 244.0f };

//------------------------------------------------------����----------------------------------------------------------

//�G�̖��O
const std::string st_Enemy = "EnemyTag";
//�G�̍U��
const std::string st_EnemyAttackTag = "EnemyAttackTag";
const std::string st_EnemyAttack = "EnemyAttack";
const std::string st_EnemyStrongAttack = "EnemyStrongAttack";


//�G�̏o�����̉�]�̌v�Z
const GSvector3 EnemyRotate{ 0.0f,180.0f,0.0f };
//�G��Hp�J���[
const GScolor EnemyHPColor{ 1.0f,0.1f,0.1f,1.0f };


// ��Z�J���[�p(glColor)
const GScolor MultiplicationColor{ 1.0f, 1.0f, 1.0f, 1.0f };
//�o���J���[
const float GenerateTime{ 0.01f };
//�U�����̃����J���[
const GScolor AttackColor{ 1.0f, 0.0f, 0.0f, 1.0f };
const float  AttackExponent{ 2.0f };
// �t���b�V���J���[
const GScolor m_FlashColor{ 1.0f, 1.0f, 0.5f, 1.0f };
//�h�炷�l
const float ElasticValue{ -0.2f };
//�q�b�g�X�g�b�v�^�C�}�[
const float HitStopTime{ 10.0f };
//�q�b�g�X�g�b�v�^�C�}�[
const float ExtictionTime{ 0.1f };
//�U���f�B���C
const float AttackDelay{ 10.0f };

//�����̃I�t�Z�b�g
const float FootOffset{ -0.1f };
//�d��
const float Gravity{ -0.09f };
//���E�m�F�̒l
const float TargerAngleValue{ 10.0f };
//�X���[�{��
const float SlowMagnification{ 0.1f };
//�ړ��ʔ{��
const float OverlapValue{ 0.5f };

//-----------------------------------------------------���b�Z�[�W-------------------------------------------------

//�����Ȃ��Ȃ�ۂ̃��b�Z�[�W
const std::string st_Message_Die = "Die";
//�����J���ۂ̃��b�Z�[�W
const std::string st_Message_IsOpen = "IsOpen";
//�q�b�g���̃��b�Z�[�W
const std::string st_Message_Hit = "Hit";
////�����J���ۃJ�������̃��b�Z�[�W
const std::string st_Message_OpenDoor = "OpenDoor";
//���݃^�[�Q�b�g�ɂ��Ă���G�̊m�F���b�Z�[�W
const std::string st_Message_Target = "Target";
//�Z���N�g�V�[���m�F�̃��b�Z�[�W
const std::string st_Message_SelectScene = "IsSelectScene";


#endif