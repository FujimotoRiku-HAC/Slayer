#ifndef SCENE_CONSTANT_H_
#define SCENE_CONSTANT_H_

#include <gslib.h>
#include "Assets.h"
//------------------------------------------------------EditScene------------------------------------------------

// �I���J�[�\���ʒu
const GSvector2 EditRectPos{ 90,170 };
//�A�r���e�BText�̈ʒu
const GSvector2 AbilityTextNamePos{ 100,400 };
//Text�؂���̑傫��
const GSvector2 EditRectScale{ 500,50 };
//�A�r���e�B�t���[���̃|�W�V����
const GSvector2 AbilityBackFramePos{ 75.0f,450.0f };
//�A�r���e�B�I���t���[���ʒu
const GSvector2 AbilityFramePos{ 70.0f,454.0f };
//�A�r���e�B�ʒu
const GSvector2 AbilityPos{5.9f,4.2f};

//�t���[���؂���̑傫��
const GSvector2 FrameRectPos{ 330.0f,30.0f };

//�X�L���t���[���̃|�W�V����
const GSvector2 SkillBackFramePos{ 75.0f,520.0f };
//�X�L���I���t���[���ʒu
const GSvector2 SkillFramePos{ 70.0f,524.0f };
//�X�L���̈ʒu
const GSvector2 SkillPos{ 7.0f,2.0f };
//�X�L��Text�̈ʒu
const GSvector2 SkillTextNamePos{ 100,480 };
//�X�L���̑傫��
const GSvector2 TextNameScale{ 0.6f,1.0f };


//�{�b�N�X�̑傫��
const GSvector2 BoxScale{ 0.4f,0.4f };
//�o�b�N�O���E���h�̑傫��
const GSvector2 FrameScale{ 0.71f,0.5f };
//�X���b�g�̑傫��
const GSvector2 SlotScale{ 0.25f,0.25f };
//�������̑傫��
const GSvector2 TextScale{ 0.2f,0.2f };
//�o�b�N�̑傫��
const GSvector2 BackGroundScale{ 1.4f,1.55f };
//�X�N���[���o�[�̑傫��
const GSvector2 ScrollScale{ 1.53f,1.2f };
//�X�N���[���o�[�؂���
const float ScrollBarRect{ 256.0f };
//�A�r���e�B�X�N���[���o�[
const GSvector2 AbilityScrollBarScaleRect{ 15.0f,75.0f };
//�X�L���X�N���[���o�[
const GSvector2 SkillScrollBarScaleRect{ 15.0f,100.0f };

// �����`��ʒu
const GSvector2 ExplanationRect{ 1250,300 };
//�����`��̑傫��
const GSvector2 ExplanationScale{ 0.7f,0.7f };
//�{�b�N�X�؂���̑傫��
const GSvector2 BoxRectScale{ 50.0f,160.0f };
//�{�b�N�X�ʒu
const GSvector2 SlotPos{ 10.0f,100.0f};

//���^�[���̈ʒu
const GSvector2 ReturnPos{ 30.0f,ScreenHeight - 150.0f };
// �󔒂̑傫��
const float BlankScale{ 5 };
const float AbilityBlankScale{ 150 };
const float SkillBlankScale{ 50 };

// ��x�ɕ\������I�����̐�
const int FieldListNum{ 6 };
// �e�N�X�`���̃Z�b�g�A�C�e���؂���
const GSvector2 TextureOfSkillField{ 500,700 };
// �e�N�X�`���̃Z�b�g�X�L���؂���
const GSvector2 TextureOfAbilityField{ 0,50 };

//-----------------------------------------�G�f�B�b�g�V�[��--------------------------------

//�g
const GSrect EditFrameRect{ -1.0f, 90.0f , 300.0f , 150.0f };

const GSvector2 EditTextPos{ 10.0f,100.0f };

const GScolor EditTextColor{ 1.0f,1.0f,1.0f,1.0f };

const GSrect EditRect{ 0.0f,0.0f,400.0f,50.0f };

const float EditDrawShift{ 75.0f };

const int EditTextNum{ 4 };

const float RectShiftPos{ 75.0f };

//----------------------------------------------------------TitleScene-------------------------------------------

//Text�؂���̑傫��
const GSvector2 TitleRectScale{ 400,50 };
//��
const float TitleTextBlankScale{ 75.0f };
//�e�L�X�g���̐�
const int TitleTextFieldNum{ 3 };

const GSvector2 TitleTextPosSet{ 130.0f,180.0f };

//----------------------------------------------------------OptionScene-------------------------------------------

//�e�L�X�g���̐�
const int OptionTextFieldNum{ 2 };
//�I�v�V�����e�L�X�g�̐؂���̑傫��
const GSvector2 OptionTextScale{ 500.0f,45.0f };
//���^�[���̈ʒu
const GSvector2 OptionReturnScale{ 860.0f,570.0f };
//�e�L�X�g�̈ʒu
const GSvector2 OptionTextPos{ 10.0f,200.0f };
//��
const float OptionBlankScale{ 140.0f };
//�X���C�_�[
const float OptionSliderValue{ 0.1f };

//BGM�ʒu
const GSrect OptionBGMRect{ 10,200,150,250 };
//SE�ʒu
const GSrect OptionSERect{ 10,340,150,390 };
//���^�[���ʒu
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

//���[�h�e�L�X�g�`��
const GSvector2 LoadTextPos{ ScreenWidth - 150.0f,ScreenHeight - 150.0f };
const GSvector2 NowLoadTextPos{ ScreenWidth / 2 - 250.0f,ScreenHeight / 2 - 100.0f };

//�m�n�v���[�h�e�L�X�g
const GSvector2 LoadCenterPos{ 64.0f,64.0f };

//---------------------------------------------------------�Q�[���v���C�V�[��--------------------------------

//�e�L�X�g�̐�
const int ClearFirstTextNum{ 1 };

const int ClearTextNum{ 3 };
//�ʒu�̕␳�l
const float ClearTextPosOffset{ 190.0f };

const GSvector2 ClearTextShiftPosOffset{ 35.0f,75.0f };


//----------------------------------------------------------ClearScene--------------------------------------------

//�N���A�V�[���̐؂���
const GSvector2 ClearRectScale{ 500.0f,45.0f };
//
const GSvector2 SceneName{ 10.0f,20.0f };

//�����N�̃|�W�V����
const GSvector2 ClearRankPos{ 100.0f,180.0f };
const GSvector2 RankPos{ 280.0f,205.0f };
const GSvector2 ClearScale{ 1.2f,1.0f };
const GSvector2 RankScale{ 1.5f,1.5f };
const GSvector2 RankRectScale{ 300.0f,45.0f };
//�����N�^�C��
const float ARankTime{ 60.0f };
const float BRankTime{ 120.0f };
const float CRankTime{ 180.0f };
//�N���A�V�[���o�b�N�O���E���h
const GSrect ClearRectBG{ 100.0f,180.0f,ScreenWidth - 100.0f,ScreenHeight - 180.0f };
//�N���A�\��
const GSvector2 ClearPos{ ScreenWidth / 2 - 200.0f, ScreenHeight / 2 - 200.0f };
//
const GSvector2 ClearTextPos{ 110.0f,180.0f };

//----------------------------------------------------------�Q�[���I�[�o�[----------------------------------

//�e�L�X�g�؂���
const GSvector2 GameOverRect{ 500.0f,60.0f };
//�Q�[���I�[�o�[�ʒu
const GSvector2 OverPos{ 250.0f,200.0f };
//�e�L�X�g�ʒu
const GSvector2 OverTextPos{ 250.0f,100.0f };
//�ʒu�ړ�
const float OverTextShiftPos{ 80.0f };
//�e�L�X�g��
const int OverTextNum{ 3 };

//----------------------------------------------------����----------------------------------------

//�V���h�E�}�b�v
const GSuint ShadowMapSize[] = { 2048,2048 };
//�V���h�E�}�b�v��K�p���鋗��
const float ShadowMapDis{ 60.0f };
//�J�X�P�[�h�V���h�E�}�b�v�̕������鋗��(�f�t�H���g��0.5)
const float ShadowMapCascade{ 0.7f };
//�V���h�E�̔Z����ݒ�
const float ShadowMapAttenuation{ 0.6f };


// �I��F
const GScolor SelectColor{ 0.0f,1.0f,1.0f,0.5f };

#endif // !EDIT_CONSTANT_H_