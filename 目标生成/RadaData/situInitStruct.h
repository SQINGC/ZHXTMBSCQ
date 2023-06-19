/*�涨�����нǶ�ֵ�ĵ�λ��Ϊ���ȡ���
        ��λ������Ϊ��ȣ�
		��������Ϊ�㣬��ͷ����ͷ������ͷ�ȷ�λ��Ϊ�㣬��Ϊ��������
		�״�͹���ˮƽ��ת������[��λ���ɨ�迪ʼ��]��[��λ���ɨ�������]˳ʱ����ת��
*/

#pragma once

// ս������
struct BattleEnvironment {
	short  terrain;				//	����, 0-ɽ��, 1-ƽԭ, 2-ɳĮ, 3-����
	short  weather;				//	����, 0-����, 1-����, 2-����, 3-����, 4-С��, 5-����, 6-����, 7-����, 8-Сѩ, 9-��ѩ, 10-��ѩ, 11-��ѩ
	double windSpeed;			//	����, ��λ����/��
	double windDirection;		//	����, ��λ����
	double temperature;			//	�¶�, ��λ�����϶�
	double humidity;			//	ʪ��, ��λ���ٷֱ�
	double barometricPressure;	//	��ѹ, ��λ��ǧ��	
	short  roadType;			//	·������, 0-����, 1-������, 2-����
};

// ָ��ϵͳ
struct CommSys {
	int maxTarNum; 	// ���Ŀ���������
};

// Ŀָ�״�
struct DirRadar {
	double	offsetx;				//	�����ָ�ӳ���ƫ��x����λ����
	double	offsety;				//	�����ָ�ӳ���ƫ��y����λ����
	double	offsetz;				//	�����ָ�ӳ���ƫ��z����λ����
	double	detectCycle;			//	ɨ�����ڣ���λ����
	short	radarType;				//	�״����� 0����е��1��һά�����2����ά�����
	double	detectAngYawStart;		//	��λ���ɨ����ʼ�ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngYawStop;		// 	��λ���ɨ������ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngPitchStart;	// 	�������ɨ����ʼ�ǣ���λ����
	double	detectAngPitchStop;		// 	�������ɨ������ǣ���λ����
	double	detectRangeYaw;			// 	������С������������нǣ���λ����
	double	fc;						// 	��Ƶ����λ��ǧ�׺��� C����(2~4GHz)��S����(4~8GHz)
	double	detectRangeMax;			// 	�ο�������Χ����λ����
	bool	typeMTI;				// 	ʹ��MTI
	bool	typeMTD;				// 	ʹ��MTD
};

// ����ϵͳ
struct FireSys {
	double	offsetx;				//	����ڻ�������ƫ��x����λ����
	double	offsety;				//	����ڻ�������ƫ��y����λ����
	double	offsetz;				//	����ڻ�������ƫ��z����λ����
	short	caliberGun;				//	���ڿھ�����λ������
	short	numberGunBarrel;		//	�����
	short	typeCarrier;			//	�������� 0�������Ĵ���1��������ʽ��2��ǣ��
	short	methodLaunching;		//	���䷽ʽ 0�����У�1�����У�2��ת�ܣ�3��ת��
	double	pitchAngGun;			//	�������ߵͽ������� ��λ����
	double	pitchRangeGun;			//	�������ߵͽǷ�Χ ��λ����
	double	disRangeGun;			//	���ڻ�����Χ ��λ����
	double	speedShootGun;			//	���� ��λ����/min	
	short	methodsShootLen;		//	������� 0��������1���̵��䣻2�������䣻3������
	short	shellNumNoShooting;		//	���ڵ��� ��λ����
	short	typeShell;				//	���ڵ��� 0��ɱ������1���ѿǴ��׵���2��Ԥ����Ƭ��
	double	initialSpeedShell;		//	������� ��λ����/��
	double	disRangeMis;			//	����������Χ ��λ����
	short	numMis;					//	����װ����
	double	verOffsetAngMis;		//	����������᷽λ�� ��λ����
	double	horOffsetAngMis;		//	���������Ǹ��������� ��λ����
	double	horOffsetAngRangeMis;	//	���������Ǹ��Ƿ�Χ ��λ����
};

// �����״�
struct SearchRadar {
	double	offsetx;				//	�����ָ�ӳ���ƫ��x����λ����
	double	offsety;				//	�����ָ�ӳ���ƫ��y����λ����
	double	offsetz;				//	�����ָ�ӳ���ƫ��z����λ����
	double	detectCycle;			//	ɨ�����ڣ���λ����
	short	radarType;				//	�״����� 0����е��1��һά�����2����ά�����
	double	detectAngYawStart;		//	��λ���ɨ����ʼ�ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngYawStop;		//	��λ���ɨ������ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngPitchStart;	//	�������ɨ����ʼ�ǣ���λ����
	double	detectAngPitchStop;		//	�������ɨ������ǣ���λ����
	double	detectRangeYaw;			//	������С����λ����
	double	fc;						// 	��Ƶ����λ��ǧ�׺��� C����(2~4GHz)��S����(4~8GHz)
	double	detectRangeMax;			//	�ο�������Χ����λ����
	bool	typeMTI;				//	ʹ��MTI
	bool	typeMTD;				//	ʹ��MTD
};

// �����״�
struct TrackRadar{
	double	offsetx;				//	�����ָ�ӳ���ƫ��x����λ����
	double	offsety;				//	�����ָ�ӳ���ƫ��y����λ����
	double	offsetz;				//	�����ָ�ӳ���ƫ��z����λ����
	short	radarType;				//	�״����� 0����е��1��һά�����2����ά�����
	double	detectAngYawStart;		//	��λ���ɨ����ʼ�ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngYawStop;		//	��λ���ɨ������ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngPitchStart;	//	�������ɨ����ʼ�ǣ���λ����
	double	detectAngPitchStop;		//	�������ɨ������ǣ���λ����	
	double	detectRangeYaw;			//	������С����λ����
	double	fc;						//	��Ƶ, ��λ��ǧ�׺���, Ka����(27-40GHz)
	double	detectRangeMax;			//	�ο�������Χ����λ����
	bool	typeMTI;				//	ʹ��MTI
	bool	typeMTD;				//	ʹ��MTD
	double	turnAzVel;				//	��λת�����ٶȣ���λ����/��
	double	turnElVel;				//	����ת�����ٶȣ���λ����/��
	double	turnAzAcc;				//	��λת���Ǽ��ٶȣ���λ����/��ƽ��
	double	turnElAcc;				//	����ת���Ǽ��ٶȣ���λ����/��ƽ��
	double	turnAzError;			//	��λ�ŷ����پ��ȣ���λ����
	double	turnElError;			//	�����ŷ����پ��ȣ���λ����
};

// ������
struct PhotTrack{
	double	offsetx;					//	�����ָ�ӳ���ƫ��x����λ����
	double	offsety;					//	�����ָ�ӳ���ƫ��y����λ����
	double	offsetz;					//	�����ָ�ӳ���ƫ��z����λ����
	double	detectAngYawStart;			//	��λ���ɨ����ʼ�ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngYawStop;			//	��λ���ɨ������ǣ�����ڳ�ͷ�ĽǶȣ���λ����
	double	detectAngPitchStart;		//	�������ɨ����ʼ�ǣ���λ����
	double	detectAngPitchStop;			//	�������ɨ������ǣ���λ����
	double	detectAngRangeYaw;			//	������С����λ����
	double	detectAngSpeedMaxPitch;		//	�����ٸߵͽ��ٶȣ���λ����/��
	double	detectAngAccMaxPitch;		//	�����ٸߵͽǼ��ٶȣ���λ����/��ƽ��
	double	detectAngSpeedMaxYaw;		//	�����ٷ�λ���ٶȣ���λ����/��
	double	detectAngAccMaxYaw;			//	�����ٷ�λ�Ǽ��ٶȣ���λ����/��ƽ��
	double	detectRangeMax;				//	������Χ����λ����
	double	servoPre;					//	�ŷ����پ��ȣ���λ����
	bool	laserWork;					//	������
	double	laserDisPre;				//	�����ྫ�ȣ���λ����
};

// �̶���ɻ�
struct FixedWing{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	double rcs;				//	RCS, ��λ��ƽ����
	short  rcsType;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	����, ��λ����
	double width;			//	��չ, ��λ����
	double height;			//	����, ��λ����
	bool   interfereFlag;	//	��Դѹ�Ƹ���, 0-�ޣ� 1-��
	double carrierFrequency;//	��Ƶ, ��λ���׺���
	double bandwidth;		//	����, ��λ���׺���
	double power;			//	����, ��λ���ֱ�����
};

// ֱ����
struct Helicopter{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	double rcs;				//	RCS, ��λ��ƽ����
	short  rcsType;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	����, ��λ����
	double width;			//	��չ, ��λ����
	double height;			//	����, ��λ����
	bool   interfereFlag;	//	��Դѹ�Ƹ���, 0-�ޣ� 1-��
	double carrierFrequency;//	��Ƶ, ��λ���׺���
	double bandwidth;		//	����, ��λ���׺���
	double power;			//	����, ��λ���ֱ�����
};

// ���˻�
struct UAV{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	double rcs;				//	RCS, ��λ��ƽ����
	short  rcsType;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	����, ��λ����
	double width;			//	��չ, ��λ����
	double height;			//	����, ��λ����
	bool   interfereFlag;	//	��Դѹ�Ƹ���, 0-�ޣ� 1-��
	double carrierFrequency;//	��Ƶ, ��λ���׺���
	double bandwidth;		//	����, ��λ���׺���
	double power;			//	����, ��λ���ֱ�����
};

// Ѳ������
struct CruiseMissile{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	double rcs;				//	RCS, ��λ��ƽ����
	short  rcsType;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	����, ��λ����
	double width;			//	��չ, ��λ����
	double height;			//	����, ��λ����
};

// ��ȷ�Ƶ�ը��
struct GuidedBomb{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	double rcs;				//	RCS, ��λ��ƽ����
	short  rcsType;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	����, ��λ����
	double width;			//	��չ, ��λ����
	double height;			//	����, ��λ����
};