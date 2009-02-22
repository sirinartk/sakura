/*!	@file
	@brief �@�\�ԍ���`

	@author Norio Nakatani
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2000, jepro, genta
	Copyright (C) 2001, jepro, MIK, Stonee, asa-o, Misaka, hor
	Copyright (C) 2002, aroka, YAZAKI, minfu, MIK, ai, genta
	Copyright (C) 2003, �S, genta, MIK, Moca
	Copyright (C) 2004, genta, zenryaku, kazika, Moca, isearch
	Copyright (C) 2005, genta, MIK, maru
	Copyright (C) 2006, aroka, �����, fon, ryoji
	Copyright (C) 2007, ryoji, genta
	Copyright (C) 2008, nasukoji, ryoji

	This source code is designed for sakura editor.
	Please contact the copyright holder to use this code for other purpose.
*/

#ifndef _FUNCCODE_H_
#define _FUNCCODE_H_

/* ����`�p(�_�~�[�Ƃ��Ă��g��) */	//Oct. 17, 2000 jepro noted
#define F_DISABLE		0	//���g�p
#define F_SEPARATOR		1	//�Z�p���[�^

#define F_MENU_FIRST 30000

/* �t�@�C������n */
#define F_FILENEW					30101	//�V�K�쐬
#define F_FILEOPEN					30102	//�J��
#define F_FILESAVE					30103	//�㏑���ۑ�
#define F_FILESAVEAS_DIALOG			30104	//���O��t���ĕۑ�
#define F_FILESAVEAS				30106	//���O��t���ĕۑ�
#define F_FILECLOSE					30105	//����(����)	//Oct. 17, 2000 jepro �u�t�@�C�������v�Ƃ����L���v�V������ύX
#define F_FILECLOSE_OPEN			30107	//���ĊJ��
#define F_FILEOPEN_DROPDOWN			30108	//�J��(�h���b�v�_�E��)
#define F_FILESAVECLOSE				30109	//�ۑ����ĕ��� Feb. 28, 2004 genta
#define F_FILESAVEALL				30120	//�㏑���ۑ� //	Jan. 24, 2005 genta
#define F_FILESAVE_QUIET			30121	//�㏑���ۑ�(���蓮��) //	Jan. 24, 2005 genta
//	Dec. 4, 2002 genta
#define F_FILE_REOPEN				30119	//���݂Ɠ��������R�[�h�łŊJ������
#define F_FILE_REOPEN_SJIS			30111	//SJIS�ŊJ������
#define F_FILE_REOPEN_JIS			30112	//JIS�ŊJ������
#define F_FILE_REOPEN_EUC			30113	//EUC�ŊJ������
#define F_FILE_REOPEN_UNICODE		30114	//Unicode�ŊJ������
#define F_FILE_REOPEN_UNICODEBE		30117	//UnicodeBE�ŊJ������
#define F_FILE_REOPEN_UTF8			30115	//UTF-8�ŊJ������
#define F_FILE_REOPEN_UTF7			30116	//UTF-7�ŊJ������
#define F_PRINT						30150	//���
#define F_PRINT_PREVIEW				30151	//����v���r���[
#define F_PRINT_PAGESETUP			30152	//����y�[�W�ݒ�	//Sept. 14, 2000 jepro �u����̃y�[�W���C�A�E�g�̐ݒ�v����u����y�[�W�ݒ�v�ɕύX
//#define F_PRINT_DIALOG				30151	//����_�C�A���O
#define F_OPEN_HHPP					30160	//������C/C++�w�b�_�t�@�C�����J��	//Feb. 9, 2001 jepro�u.c�܂���.cpp�Ɠ�����.h���J���v����ύX
#define F_OPEN_CCPP					30161	//������C/C++�\�[�X�t�@�C�����J��	//Feb. 9, 2001 jepro�u.h�Ɠ�����.c(�Ȃ����.cpp)���J���v����ύX
#define	F_OPEN_HfromtoC				30162	//������C/C++�w�b�_(�\�[�X)���J��	//Feb. 7, 2001 JEPRO �ǉ�
#define F_ACTIVATE_SQLPLUS			30170	/* Oracle SQL*Plus���A�N�e�B�u�\�� */
#define F_PLSQL_COMPILE_ON_SQLPLUS	30171	/* Oracle SQL*Plus�Ŏ��s */	//Sept. 17, 2000 jepro �����́u�R���p�C���v���u���s�v�ɓ���
#define F_BROWSE					30180	//�u���E�Y
#define F_READONLY					30185	/* �t�@�C���̃v���p�e�B */
#define F_PROPERTY_FILE				30190	/* �t�@�C���̃v���p�e�B */
#define F_EXITALLEDITORS			30194	/* �ҏW�̑S�I�� */	// 2007.02.13 ryoji �ǉ�
#define F_EXITALL					30195	/* �T�N���G�f�B�^�̑S�I�� */	//Dec. 27, 2000 JEPRO �ǉ�
#define F_NOWOPENFILE				30197	//���݊J���Ă���t�@�C��
#define F_RECENTFILE				30198	//�ŋߎg�����t�@�C��
#define F_RECENTFOLDER				30199	//�ŋߎg�����t�H���_

/* �ҏW�n */
#define F_CHAR				30200	//��������
#define F_IME_CHAR			30201	//�S�p��������
#define F_UNDO				30210	//���ɖ߂�(Undo)
#define F_REDO				30211	//��蒼��(Redo)
#define F_DELETE			30221	//�폜
#define F_DELETE_BACK		30222	//�J�[�\���O���폜
#define F_WordDeleteToStart	30230	//�P��̍��[�܂ō폜
#define F_WordDeleteToEnd	30231	//�P��̉E�[�܂ō폜
#define F_WordCut			30232	//�P��؂���
#define F_WordDelete		30233	//�P��폜
#define F_LineCutToStart	30240	//�s���܂Ő؂���(���s�P��)
#define F_LineCutToEnd		30241	//�s���܂Ő؂���(���s�P��)
#define F_LineDeleteToStart	30242	//�s���܂ō폜(���s�P��)
#define F_LineDeleteToEnd	30243	//�s���܂ō폜(���s�P��)
#define F_CUT_LINE			30244	//�s�؂���(�܂�Ԃ��P��)
#define F_DELETE_LINE		30245	//�s�폜(�܂�Ԃ��P��)
#define F_DUPLICATELINE		30250	//�s�̓�d��(�܂�Ԃ��P��)
#define F_INDENT_TAB		30260	//TAB�C���f���g
#define F_UNINDENT_TAB		30261	//�tTAB�C���f���g
#define F_INDENT_SPACE		30262	//SPACE�C���f���g
#define F_UNINDENT_SPACE	30263	//�tSPACE�C���f���g
//#define F_WORDSREFERENCE	30270	//�P�ꃊ�t�@�����X
#define F_LTRIM				30280	//��(�擪)�̋󔒂��폜	2001.12.03 hor
#define F_RTRIM				30281	//�E(����)�̋󔒂��폜	2001.12.03 hor
#define F_SORT_ASC			30282	//�I���s�̏����\�[�g	2001.12.06 hor
#define F_SORT_DESC			30283	//�I���s�̍~���\�[�g	2001.12.06 hor
#define F_MERGE				30284	//�I���s�̃}�[�W		2001.12.06 hor
#define F_RECONVERT			30285	//���j���[����̍ĕϊ��Ή� 2002.04.09  minfu 


/* �J�[�\���ړ��n */
#define F_UP				30311	//�J�[�\����ړ�
#define F_DOWN				30312	//�J�[�\�����ړ�
#define F_LEFT				30313	//�J�[�\�����ړ�
#define F_RIGHT				30314	//�J�[�\���E�ړ�
#define F_UP2				30315	//�J�[�\����ړ�(�Q�s����)
#define F_DOWN2				30316	//�J�[�\�����ړ�(�Q�s����)
#define F_WORDLEFT			30320	//�P��̍��[�Ɉړ�
#define F_WORDRIGHT			30321	//�P��̉E�[�Ɉړ�
//#define F_GOLINETOP		30330	//�s���Ɉړ�(���s�P��)
//#define F_GOLINEEND		30331	//�s���Ɉړ�(���s�P��)
#define F_GOLINETOP			30332	//�s���Ɉړ�(�܂�Ԃ��P��)
#define F_GOLINEEND			30333	//�s���Ɉړ�(�܂�Ԃ��P��)
//#define F_ROLLDOWN			30340	//�X�N���[���_�E��//Oct. 10, 2000 JEPRO ���̔��y�[�W�A�b�v�ɖ��̕ύX
//#define F_ROLLUP			30341	//�X�N���[���A�b�v//Oct. 10, 2000 JEPRO ���̔��y�[�W�_�E���ɖ��̕ύX
#define F_HalfPageUp		30340	//���y�[�W�A�b�v	//Oct. 6, 2000 JEPRO ���̂�PC-AT�݊��@�n�ɕύX(ROLL��PAGE) //Oct. 10, 2000 JEPRO ���̕ύX
#define F_HalfPageDown		30341	//���y�[�W�_�E��	//Oct. 6, 2000 JEPRO ���̂�PC-AT�݊��@�n�ɕύX(ROLL��PAGE) //Oct. 10, 2000 JEPRO ���̕ύX
#define F_1PageUp			30342	//�P�y�[�W�A�b�v	//Oct. 10, 2000 JEPRO �]���̃y�[�W�A�b�v�𔼃y�[�W�A�b�v�Ɩ��̕ύX���P�y�[�W�A�b�v��ǉ�
#define F_1PageDown			30343	//�P�y�[�W�_�E��	//Oct. 10, 2000 JEPRO �]���̃y�[�W�_�E���𔼃y�[�W�_�E���Ɩ��̕ύX���P�y�[�W�_�E����ǉ�
//#define F_DISPLAYTOP		30344	//��ʂ̐擪�Ɉړ�(������)
//#define F_DISPLAYEND		30345	//��ʂ̍Ō�Ɉړ�(������)
#define F_GOFILETOP			30350	//�t�@�C���̐擪�Ɉړ�
#define F_GOFILEEND			30351	//�t�@�C���̍Ō�Ɉړ�
#define F_CURLINECENTER		30360	//�J�[�\���s���E�B���h�E������
#define F_JUMPHIST_PREV		30370	//�ړ�����: �O��
#define F_JUMPHIST_NEXT		30371	//�ړ�����: ����
#define F_JUMPHIST_SET		30372	//���݈ʒu���ړ������ɓo�^
#define F_WndScrollDown		30380	//�e�L�X�g���P�s���փX�N���[��	// 2001/06/20 asa-o
#define F_WndScrollUp		30381	//�e�L�X�g���P�s��փX�N���[��	// 2001/06/20 asa-o
#define F_GONEXTPARAGRAPH	30382	//���̒i����
#define F_GOPREVPARAGRAPH	30383	//�O�̒i����

/* �I���n */
#define F_SELECTWORD		30400	//���݈ʒu�̒P��I��
#define F_SELECTALL			30401	//���ׂđI��
#define F_SELECTLINE		30403	//1�s�I��	// 2007.10.06 nasukoji
#define F_BEGIN_SEL			30410	//�͈͑I���J�n
#define F_UP_SEL			30411	//(�͈͑I��)�J�[�\����ړ�
#define F_DOWN_SEL			30412	//(�͈͑I��)�J�[�\�����ړ�
#define F_LEFT_SEL			30413	//(�͈͑I��)�J�[�\�����ړ�
#define F_RIGHT_SEL			30414	//(�͈͑I��)�J�[�\���E�ړ�
#define F_UP2_SEL			30415	//(�͈͑I��)�J�[�\����ړ�(�Q�s����)
#define F_DOWN2_SEL			30416	//(�͈͑I��)�J�[�\�����ړ�(�Q�s����)
#define F_WORDLEFT_SEL		30420	//(�͈͑I��)�P��̍��[�Ɉړ�
#define F_WORDRIGHT_SEL		30421	//(�͈͑I��)�P��̉E�[�Ɉړ�
//#define F_GOLINETOP_SEL		30430	//(�͈͑I��)�s���Ɉړ�(���s�P��)
//#define F_GOLINEEND_SEL		30431	//(�͈͑I��)�s���Ɉړ�(���s�P��)
#define F_GOLINETOP_SEL		30432	//(�͈͑I��)�s���Ɉړ�(�܂�Ԃ��P��)
#define F_GOLINEEND_SEL		30433	//(�͈͑I��)�s���Ɉړ�(�܂�Ԃ��P��)
//#define F_ROLLDOWN_SEL		30440	//(�͈͑I��)�X�N���[���_�E��//Oct. 10, 2000 JEPRO ���̔��y�[�W�A�b�v�ɖ��̕ύX
//#define F_ROLLUP_SEL		30441	//(�͈͑I��)�X�N���[���A�b�v//Oct. 10, 2000 JEPRO ���̔��y�[�W�_�E���ɖ��̕ύX
#define F_HalfPageUp_Sel	30440	//(�͈͑I��)���y�[�W�A�b�v	//Oct. 6, 2000 JEPRO ���̂�PC-AT�݊��@�n�ɕύX(ROLL��PAGE) //Oct. 10, 2000 JEPRO ���̕ύX
#define F_HalfPageDown_Sel	30441	//(�͈͑I��)���y�[�W�_�E��	//Oct. 6, 2000 JEPRO ���̂�PC-AT�݊��@�n�ɕύX(ROLL��PAGE) //Oct. 10, 2000 JEPRO ���̕ύX
#define F_1PageUp_Sel		30442	//(�͈͑I��)�P�y�[�W�A�b�v	//Oct. 10, 2000 JEPRO �]���̃y�[�W�A�b�v�𔼃y�[�W�A�b�v�Ɩ��̕ύX���P�y�[�W�A�b�v��ǉ�
#define F_1PageDown_Sel		30443	//(�͈͑I��)�P�y�[�W�_�E��	//Oct. 10, 2000 JEPRO �]���̃y�[�W�_�E���𔼃y�[�W�_�E���Ɩ��̕ύX���P�y�[�W�_�E����ǉ�
//#define F_DISPLAYTOP_SEL	30444	//(�͈͑I��)��ʂ̐擪�Ɉړ�(������)
//#define F_DISPLAYEND_SEL	30445	//(�͈͑I��)��ʂ̍Ō�Ɉړ�(������)
#define F_GOFILETOP_SEL		30450	//(�͈͑I��)�t�@�C���̐擪�Ɉړ�
#define F_GOFILEEND_SEL		30451	//(�͈͑I��)�t�@�C���̍Ō�Ɉړ�
#define F_GONEXTPARAGRAPH_SEL	30482	//(�͈͑I��)���̒i����
#define F_GOPREVPARAGRAPH_SEL	30483	//(�͈͑I��)�O�̒i����


/* ��`�I���n */
//#define F_BOXSELALL		30500	//��`�ł��ׂđI��
#define	F_BEGIN_BOX			30510	//��`�͈͑I���J�n
//Oct. 17, 2000 JEPRO �ȉ��ɋ�`�I���̃R�}���h���̂ݏ������Ă�����
//#define F_UP_BOX			30511	//(��`�I��)�J�[�\����ړ�
//#define F_DOWN_BOX			30512	//(��`�I��)�J�[�\�����ړ�
//#define F_LEFT_BOX			30513	//(��`�I��)�J�[�\�����ړ�
//#define F_RIGHT_BOX			30514	//(��`�I��)�J�[�\���E�ړ�
//#define F_UP2_BOX			30515	//(��`�I��)�J�[�\����ړ�(�Q�s����)
//#define F_DOWN2_BOX			30516	//(��`�I��)�J�[�\�����ړ�(�Q�s����)
//#define F_WORDLEFT_BOX		30520	//(��`�I��)�P��̍��[�Ɉړ�
//#define F_WORDRIGHT_BOX		30521	//(��`�I��)�P��̉E�[�Ɉړ�
////#define F_GOLINETOP_BOX		30530	//(��`�I��)�s���Ɉړ�(���s�P��)
////#define F_GOLINEEND_BOX		30531	//(��`�I��)�s���Ɉړ�(���s�P��)
//#define F_GOLINETOP_BOX		30532	//(��`�I��)�s���Ɉړ�(�܂�Ԃ��P��)
//#define F_GOLINEEND_BOX		30533	//(��`�I��)�s���Ɉړ�(�܂�Ԃ��P��)
//#define F_HalfPageUp_Box	30540	//(��`�I��)���y�[�W�A�b�v
//#define F_HalfPageDown_Box	30541	//(��`�I��)���y�[�W�_�E��
//#define F_1PageUp_Box		30542	//(��`�I��)�P�y�[�W�A�b�v
//#define F_1PageDown_Box		30543	//(��`�I��)�P�y�[�W�_�E��
////#define F_DISPLAYTOP_BOX	30444	//(��`�I��)��ʂ̐擪�Ɉړ�(������)
////#define F_DISPLAYEND_BOX	30445	//(��`�I��)��ʂ̍Ō�Ɉړ�(������)
//#define F_GOFILETOP_BOX		30550	//(��`�I��)�t�@�C���̐擪�Ɉړ�
//#define F_GOFILEEND_BOX		30551	//(��`�I��)�t�@�C���̍Ō�Ɉړ�


/* �N���b�v�{�[�h�n */
#define F_CUT						30601	//�؂���(�I��͈͂��N���b�v�{�[�h�ɃR�s�[���č폜)
#define F_COPY						30602	//�R�s�[(�I��͈͂��N���b�v�{�[�h�ɃR�s�[)
#define F_COPY_ADDCRLF				30608	//�܂�Ԃ��ʒu�ɉ��s�����ăR�s�[
#define F_COPY_CRLF					30603	//CRLF���s�ŃR�s�[
#define F_PASTE						30604	//�\��t��(�N���b�v�{�[�h����\��t��)
#define F_PASTEBOX					30605	//��`�\��t��(�N���b�v�{�[�h�����`�\��t��)
#define F_INSTEXT					30606	//�e�L�X�g��\��t��
#define F_ADDTAIL					30607	//�Ō�Ƀe�L�X�g��ǉ�
#define F_COPYLINES					30610	//�I��͈͓��S�s�R�s�[
#define F_COPYLINESASPASSAGE		30611	//�I��͈͓��S�s���p���t���R�s�[
#define F_COPYLINESWITHLINENUMBER	30612	//�I��͈͓��S�s�s�ԍ��t���R�s�[
#define F_COPYPATH					30620	//���̃t�@�C���̃p�X�����N���b�v�{�[�h�ɃR�s�[
#define F_COPYTAG					30621	//���̃t�@�C���̃p�X���ƃJ�[�\���ʒu���R�s�[
#define F_COPYFNAME					30622	//���̃t�@�C�������N���b�v�{�[�h�ɃR�s�[ // 2002/2/3 aroka
//Sept. 16, 2000 JEPRO �V���[�g�J�b�g�L�[�����܂������Ȃ��̂Ŏ��s�͎E���Ă���	//Dec. 25, 2000 ����
#define F_CREATEKEYBINDLIST			30630	//�L�[���蓖�Ĉꗗ���R�s�[ //Sept. 15, 2000 JEPRO ��̍s��IDM_TEST�̂܂܂ł͂��܂������Ȃ��̂�F�ɕς��ēo�^


/* �}���n */
#define F_INS_DATE				30790	//���t�}��
#define F_INS_TIME				30791	//�����}��
#define F_CTRL_CODE_DIALOG		30792	//�R���g���[���R�[�h�̓���(�_�C�A���O)	//@@@ 2002.06.02 MIK


/* �ϊ��n */
#define F_TOLOWER				30800	//������
#define F_TOUPPER				30801	//�啶��
#define F_TOHANKAKU				30810	/* �S�p�����p */
#define F_TOHANKATA				30817	/* �S�p�J�^�J�i�����p�J�^�J�i */	//Aug. 29, 2002 ai
#define F_TOZENKAKUKATA			30811	/* ���p�{�S�Ђ灨�S�p�E�J�^�J�i */	//Sept. 17, 2000 jepro �������u���p���S�p�J�^�J�i�v����ύX
#define F_TOZENKAKUHIRA			30812	/* ���p�{�S�J�^���S�p�E�Ђ炪�� */	//Sept. 17, 2000 jepro �������u���p���S�p�Ђ炪�ȁv����ύX
#define F_HANKATATOZENKAKUKATA	30813	/* ���p�J�^�J�i���S�p�J�^�J�i */
#define F_HANKATATOZENKAKUHIRA	30814	/* ���p�J�^�J�i���S�p�Ђ炪�� */
#define F_TOZENEI				30815	/* ���p�p�����S�p�p�� */			//July. 30, 2001 Misaka
#define F_TOHANEI				30816	/* �S�p�p�������p�p�� */			//@@@ 2002.2.11 YAZAKI
#define F_TABTOSPACE			30830	/* TAB���� */
#define F_SPACETOTAB			30831	/* �󔒁�TAB *///#### Stonee, 2001/05/27
#define F_CODECNV_AUTO2SJIS		30850	/* �������ʁ�SJIS�R�[�h�ϊ� */
#define F_CODECNV_EMAIL			30851	//E-Mail(JIS��SJIS)�R�[�h�ϊ�
#define F_CODECNV_EUC2SJIS		30852	//EUC��SJIS�R�[�h�ϊ�
#define F_CODECNV_UNICODE2SJIS	30853	//Unicode��SJIS�R�[�h�ϊ�
#define F_CODECNV_UNICODEBE2SJIS 30856	/*Unicode��SJIS�R�[�h�ϊ�*/
#define F_CODECNV_UTF82SJIS		30854	/* UTF-8��SJIS�R�[�h�ϊ� */
#define F_CODECNV_UTF72SJIS		30855	/* UTF-7��SJIS�R�[�h�ϊ� */
#define F_CODECNV_SJIS2JIS		30860	/* SJIS��JIS�R�[�h�ϊ� */
#define F_CODECNV_SJIS2EUC		30861	/* SJIS��EUC�R�[�h�ϊ� */
#define F_CODECNV_SJIS2UTF8		30862	/* SJIS��UTF-8�R�[�h�ϊ� */
#define F_CODECNV_SJIS2UTF7		30863	/* SJIS��UTF-7�R�[�h�ϊ� */
#define F_BASE64DECODE			30870	//Base64�f�R�[�h���ĕۑ�
#define F_UUDECODE				30880	//uudecode���ĕۑ�	//Oct. 17, 2000 jepro �������u�I�𕔕���UUENCODE�f�R�[�h�v����ύX


/* �����n */
#define F_SEARCH_DIALOG		30901	//����(�P�ꌟ���_�C�A���O)
#define F_SEARCH_NEXT		30902	//��������
#define F_SEARCH_PREV		30903	//�O������
#define F_REPLACE_DIALOG	30904	//�u��(�u���_�C�A���O)
#define F_REPLACE			30906	//�u��(���s)
#define F_REPLACE_ALL		30907	//���ׂĒu��(���s)
#define F_SEARCH_CLEARMARK	30905	//�����}�[�N�̃N���A
#define F_JUMP_SRCHSTARTPOS	30909	//�����J�n�ʒu�֖߂�	// 02/06/26 ai
#define F_SEARCH_BOX		30908	//����(�{�b�N�X)	//@@@ 2002.06.15 MIK
#define F_GREP_DIALOG		30910	//Grep
#define F_GREP				30911	//Grep
#define F_JUMP_DIALOG		30920	//�w��s�փW�����v
#define F_JUMP				30921	//�w��s�փW�����v
#define F_OUTLINE			30930	//�A�E�g���C�����
#define F_OUTLINE_TOGGLE	30931	//�A�E�g���C�����(toggle) // 20060201 aroka
#define F_TAGJUMP			30940	//�^�O�W�����v�@�\
#define F_TAGJUMPBACK		30941	//�^�O�W�����v�o�b�N�@�\
#define	F_TAGJUMP_LIST		30942	//�^�O�W�����v���X�g	//@@@ 2003.04.13 MIK
#define	F_TAGS_MAKE			30943	//�^�O�t�@�C���̍쐬	//@@@ 2003.04.13 MIK
#define	F_DIRECT_TAGJUMP	30944	//�_�C���N�g�^�O�W�����v	//@@@ 2003.04.15 MIK
#define F_TAGJUMP_CLOSE		30945	//���ă^�O�W�����v(���E�B���h�Eclose) // Apr. 03. 2003 genta
#define F_TAGJUMP_KEYWORD	30946	//�L�[���[�h���w�肵�ă_�C���N�g�^�O�W�����v	//@@@ 2005.03.31 MIK
#define F_COMPARE			30950	//�t�@�C�����e��r
#define F_BRACKETPAIR		30960	//�Ί��ʂ̌���
#define F_BOOKMARK_SET		30970	//�u�b�N�}�[�N�ݒ�E����
#define F_BOOKMARK_NEXT		30971	//���̃u�b�N�}�[�N��
#define F_BOOKMARK_PREV		30972	//�O�̃u�b�N�}�[�N��
#define F_BOOKMARK_RESET	30973	//�u�b�N�}�[�N�̑S����
#define F_BOOKMARK_VIEW		30974	//�u�b�N�}�[�N�̈ꗗ
#define F_BOOKMARK_PATTERN	30975	//�p�^�[���Ɉ�v����s���}�[�N
#define F_DIFF_DIALOG		30976	//DIFF�����\��(�_�C�A���O)	//@@@ 2002.05.25 MIK
#define F_DIFF				30977	//DIFF�����\��	//@@@ 2002.05.25 MIK
#define F_DIFF_NEXT			30978	//���̍�����	//@@@ 2002.05.25 MIK
#define F_DIFF_PREV			30979	//�O�̍�����	//@@@ 2002.05.25 MIK
#define F_DIFF_RESET		30980	//�����̑S����	//@@@ 2002.05.25 MIK
#define F_ISEARCH_NEXT	    30981	//�O���C���N�������^���T�[�` //2004.10.13 isearch
#define F_ISEARCH_PREV		30982	//����C���N�������^���T�[�` //2004.10.13 isearch
#define F_ISEARCH_REGEXP_NEXT   30983  //�O�����K�\���C���N�������^���T�[�`  //2004.10.13 isearch
#define F_ISEARCH_REGEXP_PREV   30984  //������K�\���C���N�������^���T�[�`  //2004.10.13 isearch
#define F_ISEARCH_MIGEMO_NEXT   30985  //�O��MIGEMO�C���N�������^���T�[�`    //2004.10.13 isearch
#define F_ISEARCH_MIGEMO_PREV   30986  //���MIGEMO�C���N�������^���T�[�`    //2004.10.13 isearch


/* ���[�h�؂�ւ��n */
#define F_CHGMOD_INS		31001	//�}���^�㏑�����[�h�؂�ւ�
#define F_CHGMOD_EOL_CRLF	31081	//���͉��s�R�[�h�w��(CRLF)	// 2003.06.08 Moca
#define F_CHGMOD_EOL_LF		31082	//���͉��s�R�[�h�w��(LF)	// 2003.06.08 Moca
#define F_CHGMOD_EOL_CR		31083	//���͉��s�R�[�h�w��(CR)	// 2003.06.08 Moca
#define F_CANCEL_MODE		31099	//�e�탂�[�h�̎�����

/* �ݒ�n */
#define F_SHOWTOOLBAR		31100	/* �c�[���o�[�̕\�� */
#define F_SHOWFUNCKEY		31101	/* �t�@���N�V�����L�[�̕\�� */
#define F_SHOWSTATUSBAR		31102	/* �X�e�[�^�X�o�[�̕\�� */
#define F_SHOWTAB			31103	/* �^�u�̕\�� */	//@@@ 2003.06.10 MIK
#define F_TYPE_LIST			31110	/* �^�C�v�ʐݒ�ꗗ */
#define F_OPTION_TYPE		31111	/* �^�C�v�ʐݒ� */
#define F_OPTION			31112	/* ���ʐݒ� */
#define	F_FAVORITE			31113	//�����̊Ǘ�	//@@@ 2003.04.08 MIK

//From here �ݒ�_�C�A���O�p�̋@�\�ԍ���p��  Stonee, 2001/05/18
#define F_TYPE_SCREEN		31115	/* �^�C�v�ʐݒ�w�X�N���[���x */
#define F_TYPE_COLOR		31116	/* �^�C�v�ʐݒ�w�J���[�x */
#define F_TYPE_HELPER		31117	/* �^�C�v�ʐݒ�w�x���x */	//Jul. 03, 2001 JEPRO �ǉ�
#define F_TYPE_REGEX_KEYWORD	31118	/* �^�C�v�ʐݒ�w���K�\���L�[���[�h�x */	//@@@ 2001.11.17 add MIK
#define F_TYPE_KEYHELP		31119	/* �^�C�v�ʐݒ�w�L�[���[�h�w���v�x */	// 2006.10.06 ryoji �ǉ�
#define F_OPTION_GENERAL	32000	/* ���ʐݒ�w�S�ʁx */
#define F_OPTION_WINDOW		32001	/* ���ʐݒ�w�E�B���h�E�x */
#define F_OPTION_EDIT		32002	/* ���ʐݒ�w�ҏW�x */
#define F_OPTION_FILE		32003	/* ���ʐݒ�w�t�@�C���x */
#define F_OPTION_BACKUP		32004	/* ���ʐݒ�w�o�b�N�A�b�v�x */
#define F_OPTION_FORMAT		32005	/* ���ʐݒ�w�����x */
//#define F_OPTION_URL		32006	/* ���ʐݒ�w�N���b�J�u��URL�x */
#define F_OPTION_GREP		32007	/* ���ʐݒ�wGrep�x */
#define F_OPTION_KEYBIND	32008	/* ���ʐݒ�w�L�[���蓖�āx */
#define F_OPTION_CUSTMENU	32009	/* ���ʐݒ�w�J�X�^�����j���[�x */
#define F_OPTION_TOOLBAR	32010	/* ���ʐݒ�w�c�[���o�[�x */
#define F_OPTION_KEYWORD	32011	/* ���ʐݒ�w�����L�[���[�h�x */
#define F_OPTION_HELPER		32012	/* ���ʐݒ�w�x���x */
//To here  Stonee, 2001/05/18
#define F_OPTION_MACRO		32013	/* ���ʐݒ�w�}�N���x */
#define F_OPTION_FNAME		32014	/* ���ʐݒ�w�t�@�C�����\���x */
#define F_OPTION_TAB		32015	/* ���ʐݒ�w�^�u�x*/ // Feb. 11, 2007 genta �ǉ�

#define F_FONT				31120	/* �t�H���g�ݒ� */
#define F_WRAPWINDOWWIDTH	31140	//���݂̃E�B���h�E���Ő܂�Ԃ� */	//Oct. 7, 2000 JEPRO WRAPWINDIWWIDTH �� WRAPWINDOWWIDTH �ɕύX
#define F_TMPWRAPNOWRAP		31141	// �܂�Ԃ��Ȃ��i�ꎞ�ݒ�j			// 2008.05.30 nasukoji
#define F_TMPWRAPSETTING	31142	// �w�茅�Ő܂�Ԃ��i�ꎞ�ݒ�j		// 2008.05.30 nasukoji
#define F_TMPWRAPWINDOW		31143	// �E�[�Ő܂�Ԃ��i�ꎞ�ݒ�j		// 2008.05.30 nasukoji


/* �}�N���n */
#define F_RECKEYMACRO		31250	/* �L�[�}�N���̋L�^�J�n�^�I�� */
#define F_SAVEKEYMACRO		31251	/* �L�[�}�N���̕ۑ� */
#define F_LOADKEYMACRO		31252	/* �L�[�}�N���̓ǂݍ��� */
#define F_EXECKEYMACRO		31253	/* �L�[�}�N���̎��s */
#define F_EXECEXTMACRO		31254	/* ���O���w�肵�ă}�N�����s */
//	From Here Sept. 20, 2000 JEPRO ����CMMAND��COMMAND�ɕύX
//	#define F_EXECCMMAND		31270	/* �O���R�}���h���s */
#define F_EXECCOMMAND_DIALOG	31270	/* �O���R�}���h���s */
#define F_EXECCOMMAND		31271	/* �O���R�}���h���s */
//	To Here Sept. 20, 2000

//	Jul. 4, 2000 genta
#define F_USERMACRO_0		31600	/* �o�^�}�N���J�n */


/* �J�X�^�����j���[ */
#define F_MENU_RBUTTON		31580	/* �E�N���b�N���j���[ */
#define F_CUSTMENU_1		31501	/* �J�X�^�����j���[1 */
#define F_CUSTMENU_2		31502	/* �J�X�^�����j���[2 */
#define F_CUSTMENU_3		31503	/* �J�X�^�����j���[3 */
#define F_CUSTMENU_4		31504	/* �J�X�^�����j���[4 */
#define F_CUSTMENU_5		31505	/* �J�X�^�����j���[5 */
#define F_CUSTMENU_6		31506	/* �J�X�^�����j���[6 */
#define F_CUSTMENU_7		31507	/* �J�X�^�����j���[7 */
#define F_CUSTMENU_8		31508	/* �J�X�^�����j���[8 */
#define F_CUSTMENU_9		31509	/* �J�X�^�����j���[9 */
#define F_CUSTMENU_10		31510	/* �J�X�^�����j���[10 */
#define F_CUSTMENU_11		31511	/* �J�X�^�����j���[11 */
#define F_CUSTMENU_12		31512	/* �J�X�^�����j���[12 */
#define F_CUSTMENU_13		31513	/* �J�X�^�����j���[13 */
#define F_CUSTMENU_14		31514	/* �J�X�^�����j���[14 */
#define F_CUSTMENU_15		31515	/* �J�X�^�����j���[15 */
#define F_CUSTMENU_16		31516	/* �J�X�^�����j���[16 */
#define F_CUSTMENU_17		31517	/* �J�X�^�����j���[17 */
#define F_CUSTMENU_18		31518	/* �J�X�^�����j���[18 */
#define F_CUSTMENU_19		31519	/* �J�X�^�����j���[19 */
#define F_CUSTMENU_20		31520	/* �J�X�^�����j���[20 */
#define F_CUSTMENU_21		31521	/* �J�X�^�����j���[21 */
#define F_CUSTMENU_22		31522	/* �J�X�^�����j���[22 */
#define F_CUSTMENU_23		31523	/* �J�X�^�����j���[23 */
#define F_CUSTMENU_24		31524	/* �J�X�^�����j���[24 */

#define F_CUSTMENU_BASE		31500	/* �J�X�^�����j���[��ԍ� */

/* �E�B���h�E�n */
#define F_SPLIT_V			31310	//�㉺�ɕ���	//Sept. 17, 2000 jepro �����́u�c�v���u�㉺�Ɂv�ɕύX
#define F_SPLIT_H			31311	//���E�ɕ���	//Sept. 17, 2000 jepro �����́u���v���u���E�Ɂv�ɕύX
#define F_SPLIT_VH			31312	//�c���ɕ���	//Sept. 17, 2000 jepro �����Ɂu�Ɂv��ǉ�
#define F_WINCLOSE			31320	//�E�B���h�E�����
#define F_WIN_CLOSEALL		31321	//���ׂẴE�B���h�E�����	//Oct. 17, 2000 JEPRO ���O��ύX(F_FILECLOSEALL��F_WIN_CLOSEALL)
#define F_CASCADE			31330	//�d�˂ĕ\��
#define F_TILE_V			31331	//�㉺�ɕ��ׂĕ\��
#define F_TILE_H			31332	//���E�ɕ��ׂĕ\��
#define F_BIND_WINDOW		31333	//�������ĕ\��	2004.07.14 kazika
#define F_TOPMOST			31334	//��Ɏ�O�ɕ\�� // 2004-09-21 Moca
#define F_NEXTWINDOW		31340	//���̃E�B���h�E
#define F_PREVWINDOW		31341	//�O�̃E�B���h�E
#define F_WINLIST			31336	//�J���Ă���E�B���h�E�ꗗ�|�b�v�A�b�v�\��	// 2006.03.23 fon
#define F_MAXIMIZE_V		31350	//�c�����ɍő剻
#define F_MINIMIZE_ALL		31351	//���ׂčŏ���		//Sept. 17, 2000 jepro �����́u�S�āv���u���ׂāv�ɓ���
#define F_MAXIMIZE_H		31352	//�������ɍő剻	//2001.02.10 by MIK
#define F_REDRAW			31360	//�ĕ`��
#define F_WIN_OUTPUT		31370	//�A�E�g�v�b�g�E�B���h�E�\��
#define F_GROUPCLOSE		31380	/* �O���[�v����� */	// 2007.06.20 ryoji
#define F_NEXTGROUP			31381	/* ���̃O���[�v */	// 2007.06.20 ryoji
#define F_PREVGROUP			31382	/* �O�̃O���[�v */	// 2007.06.20 ryoji
#define F_TAB_MOVERIGHT		31383	/* �^�u���E�Ɉړ� */	// 2007.06.20 ryoji
#define F_TAB_MOVELEFT		31384	/* �^�u�����Ɉړ� */	// 2007.06.20 ryoji
#define F_TAB_SEPARATE		31385	/* �V�K�O���[�v */	// 2007.06.20 ryoji
#define F_TAB_JOINTNEXT		31386	/* ���̃O���[�v�Ɉړ� */	// 2007.06.20 ryoji
#define F_TAB_JOINTPREV		31387	/* �O�̃O���[�v�Ɉړ� */	// 2007.06.20 ryoji


/* �x�� */
#define F_HOKAN				31430		/* ���͕⊮ */
#define F_TOGGLE_KEY_SEARCH	31431		/* �L�����b�g�ʒu�̒P���������������@�\ON-OFF */	// 2006.03.24 fon
//Sept. 16, 2000��Nov. 25, 2000 JEPRO //�V���[�g�J�b�g�L�[�����܂������Ȃ��̂ŎE���Ă���������2�s���C���E����
#define F_HELP_CONTENTS		31440		/* �w���v�ڎ� */			//Nov. 25, 2000 JEPRO �ǉ�
#define F_HELP_SEARCH		31441		/* �w���v�L�[���[�h���� */	//Nov. 25, 2000 JEPRO �ǉ�
#define F_MENU_ALLFUNC		31445		/* �R�}���h�ꗗ */
#define F_EXTHELP1			31450		/* �O���w���v�P */
#define F_EXTHTMLHELP		31451		/* �O��HTML�w���v */
#define F_ABOUT				31455		/* �o�[�W������� */	//Dec. 24, 2000 JEPRO �ǉ�


/* ���̑� */
//#define F_SENDMAIL		31570		/* ���[�����M */	//Oct. 17, 2000 JEPRO ���[���@�\�͎���ł���̂ŃR�����g�A�E�g�ɂ���

//	Windows 95�̐���ɂ��CWM_COMMAND�Ŏg���@�\�ԍ��Ƃ���32768�ȏ�̒l��p���邱�Ƃ��ł��܂���D
//	���j���[���Ŏg���Ȃ��}�N����p�̃R�}���h�ɂ͂���ȏ�̒l�����蓖�Ă܂��傤�D

//	���j���[����͒��ڌĂ΂�Ȃ����A����ID����ԐړI�ɌĂ΂��@�\
#define F_MENU_NOT_USED_FIRST 32768
#define F_CHGMOD_EOL          32800		// ���͉��s�R�[�h�w�� 2003.06.23 Moca
#define F_SET_QUOTESTRING     32801		// ���ʐݒ�: ���p���̐ݒ�	2005.01.29 genta
#define F_TRACEOUT            32802		// �}�N���p�A�E�g�v�b�g�E�C���h�E�ɏo��	2006.04.26 maru
#define F_PUTFILE             32803 	// ��ƒ��t�@�C���̈ꎞ�o�� 2006.12.10 maru
#define F_INSFILE             32804 	// �L�����b�g�ʒu�Ƀt�@�C���}�� 2006.12.10 maru
#define F_TEXTWRAPMETHOD      32805		// �e�L�X�g�̐܂�Ԃ����@			// 2008.05.30 nasukoji

#define F_FUNCTION_FIRST  40000 // 2003-02-21 �S ����ȏゾ�Ɗ֐�

#define F_GETFILENAME     40001 /* �ҏW���̃t�@�C�������擾���� */
#define F_GETSELECTED     40002 // Oct. 19, 2002 genta �I��͈͂̎擾
#define F_EXPANDPARAMETER 40003 // 2003-02-21 �S �R�}���h���C���p�����[�^�W�J
#define F_GETLINESTR      40004 // �w��s�_���f�[�^���擾���� 2003.06.25 Moca
#define F_GETLINECOUNT    40005 // �_���s�����擾���� 2003.06.25 Moca
#define F_CHGTABWIDTH     40006 // �^�u�T�C�Y���擾�A�ݒ肷�� 2004.03.16 zenryaku
#define F_ISTEXTSELECTED  40007 // �e�L�X�g���I������Ă��邩 2005.7.30 maru
#define F_GETSELLINEFROM  40008 // �I���J�n�s�̎擾 2005.7.30 maru
#define F_GETSELCOLMFROM  40009 // �I���J�n���̎擾 2005.7.30 maru
#define F_GETSELLINETO    40010 // �I���I���s�̎擾 2005.7.30 maru
#define F_GETSELCOLMTO    40011 // �I���I�����̎擾 2005.7.30 maru
#define F_ISINSMODE       40012 // �}���^�㏑�����[�h�̎擾 2005.7.30 maru
#define F_GETCHARCODE     40013 // �����R�[�h�擾 2005.07.31 maru
#define F_GETLINECODE     40014 // ���s�R�[�h�擾 2005.08.05 maru
#define F_ISPOSSIBLEUNDO  40015 // Undo�\�����ׂ� 2005.08.05 maru
#define F_ISPOSSIBLEREDO  40016 // Redo�\�����ׂ� 2005.08.05 maru
#define F_CHGWRAPCOLM     40017 // �܂�Ԃ������擾�A�ݒ肷�� 2008.06.19 ryoji

//	2005.01.10 genta ISearch�p�⏕�R�[�h
#define F_ISEARCH_ADD_CHAR	0x10001	//	Incremental Search��1�����֒ǉ�
#define F_ISEARCH_ADD_STR	0x10002	//	Incremental Search�֕�����֒ǉ�
#define F_ISEARCH_DEL_BACK	0x10003	//	Incremental Search�̖�������1�����폜

/* �@�\�ꗗ�Ɋւ���f�[�^�錾 */
namespace nsFuncCode{
	extern const char*	ppszFuncKind[];
	extern const int	nFuncKindNum;
	extern const int	pnFuncListNumArr[];
	extern const int*	ppnFuncListArr[];
	extern const int	nFincListNumArrNum;
};
///////////////////////////////////////////////////////////////////////
#endif /* _FUNCCODE_H_ */


/*[EOF]*/