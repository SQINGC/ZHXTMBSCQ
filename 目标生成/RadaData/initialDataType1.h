
/******************************************************************************/

// ̬��װ�����ݷ������·�
// ��һ�����·��붨������Ϣ���ڵ������Ϣ�ͽڵ����Ϣ
// �ڶ������·����ڵ��ʼ������

// ����ѡ��̬���ļ������󣬽��е�һ��

// ��һ�����ݰ���ʽ���£�
// ��ͷ����Ϣ����Ϊ COMMAND��2����ָ������Ϊ CommondSituInit��5��
// ��������Ϊ 
// ̬��ID|���沽��|ԭ������;
// �ڵ�ID1|���������ID1,���������ID2;
// �ڵ�ID2|���������ID1,���������ID2;
// .....@
// ʵ������(ָ���𡢻���������)|ʵ��ID|����,γ��,�߶�,��λ,����,��ת|��������ID1,��������ID2,��������ID3,��������ID4|����ʵ��ID;
// .....
// ע������ڵ��������ID�������ֵΪ4������������Ϊ-1��������ڵ������������ID������ڵ��н��в��ң�ȷ������λ��

// ����25|20|120,39,700;401|40101,40102;501|50101,50102;.....

// ���ڵ��յ���һ�������ݰ�����Ӧ��ָ�Ӧ��ָ���ͷ����Ϣ����Ϊ COMMAND��2����ָ������Ϊ CommondSituInitReturn��6��
// ���ؽڵ��յ����нڵ��Ӧ��ָ��󣬽��еڶ��������·�

// �ڶ������ݰ���ʽ���£�
// ��ͷ����Ϣ����Ϊ COMMAND��2����ָ������Ϊ CommondSituBind��7��
// ��������Ϊ ����ʼ������ID+��ʼ���ṹ�塱,��ʼ������IDΪ4�ֽ�����

// ���ڵ��յ��ڶ��������ݰ�����Ӧ��ָ�Ӧ��ָ���ͷ����Ϣ����ΪCOMMAND��2����ָ������ΪCommandSituBindReturn��8��

/******************************************************************************/
/*
// ս������
struct BattleEnvironment {
	short Terrain;				//	����, 0-ɽ��, 1-ƽԭ, 2-ɳĮ, 3-����
	short Weather;				//	����, 0-����, 1-����, 2-����, 3-����, 4-С��, 5-����, 6-����, 7-����, 8-Сѩ, 9-��ѩ, 10-��ѩ, 11-��ѩ
	double WindSpeed;			//	����, ��/��
	double WindDirection;		//	����, ��
	double Temperature;			//	�¶�, ���϶�
	double Humidity;			//	ʪ��, �ٷֱ�
	double BarometricPressure;	//	��ѹ, ����	
	short RoadType;				//	·������, 0-����, 1-������, 2-����
};

// ָ�ӳ�
struct CommCar {
	double lon;		//	����
	double lat;		//	γ��
	double alt;		//	�߶�
	double yaw;		//	��λ��
	double pitch;	//	������
	double roll;	//	��ת��
};

// ָ��ϵͳ
struct CommSys {
	int MaxTarNum; 	// ���Ŀ���������
};

// Ŀָ�״�
struct DirRadar {
	double	Offset_x;			//	�����ָ�ӳ���ƫ��x����λ����
	double	Offset_y;			//	�����ָ�ӳ���ƫ��y����λ����
	double	Offset_z;			//	�����ָ�ӳ���ƫ��z����λ����
	short	DetectCycle;		//	ɨ�����ڣ���λ����
	short	RadarType;			//	�״����� 0����е��1��һά�����2����ά�����
	double	DetectAng_Yaw_Start;//	��λ���ɨ�����Ľǿ�ʼ����λ����
	double	DetectAng_Yaw_Stop;	// 	��λ���ɨ�����Ľǽ�������λ����
	double	DetectRange_Yaw;	// 	��λ���ɨ�跶Χ����λ����
	double	DetectAng_Pitch;	// 	�������ɨ�����Ľǣ���λ����
	double	DetectRange_Pitch;	// 	�������ɨ�跶Χ����λ����
	short	Fc;					// 	��Ƶ 0��C����(2~4)��1��S����(4~8)
	double	DetectRangeMax;		// 	�ο�������Χ����λ����
	bool	Type_MTI;			// 	ʹ��MTI
	bool	Type_MTD;			// 	ʹ��MTD
};

// ������
struct FireCar {
	double lon;		// 	����
	double lat;		// 	γ��
	double alt;		// 	�߶�
	double yaw;		// 	��λ��
	double pitch;	// 	������
	double roll;	// 	��ת��
};

// ����ϵͳ
struct FireSys {
	double	Offset_x;				//	����ڻ�������ƫ��x����λ����
	double	Offset_y;				//	����ڻ�������ƫ��y����λ����
	double	Offset_z;				//	����ڻ�������ƫ��z����λ����
	short	Caliber_Gun;			//	���ڿھ�����λ������
	short	Number_GunBarrel;		//	�����
	short	Type_Carrier;			//	�������� 0�������Ĵ���1��������ʽ��2��ǣ��
	short	Method_Launching;		//	���䷽ʽ 0�����У�1�����У�2��ת�ܣ�3��ת��
	double	PitchAng_Gun;			//	�������ߵͽ������� ��λ����
	double	PitchRange_Gun;			//	�������ߵͽǷ�Χ ��λ����
	double	DisRange_Gun;			//	���ڻ�����Χ ��λ����
	double	Speed_Shoot_Gun;		//	���� ��λ����/min	
	short	Methods_ShootLen;		//	������� 0��������1���̵��䣻2�������䣻3������
	short	ShellNum_NoShooting;	//	���ڵ��� ��λ����
	short	Type_Shell;				//	���ڵ��� 0��ɱ������1���ѿǴ��׵���2��Ԥ����Ƭ��
	double	InitialSpeed_Shell;		//	������� ��λ����/��
	double	DisRange_Mis;			//	����������Χ ��λ����
	short	Num_Mis;				//	����װ����
	double	VerOffsetAng_Mis;		//	����������᷽λ�� ��λ����
	double	HorOffsetAng_Mis;		//	���������Ǹ��������� ��λ����
	double	HorOffsetAngRange_Mis;	//	���������Ǹ��Ƿ�Χ ��λ����
};

// �����״�
struct TearchRadar {
	double	Offset_x;			//	�����ָ�ӳ���ƫ��x����λ����
	double	Offset_y;			//	�����ָ�ӳ���ƫ��y����λ����
	double	Offset_z;			//	�����ָ�ӳ���ƫ��z����λ����
	short	DetectCycle;		//	ɨ�����ڣ���λ����
	short	RadarType;			//	�״����� 0����е��1��һά�����2����ά�����
	double	DetectAng_Yaw_Start;//	��λ���ɨ�����Ľǿ�ʼ����λ����
	double	DetectAng_Yaw_Stop;	//	��λ���ɨ�����Ľǽ�������λ����
	double	DetectRange_Yaw;	//	��λ���ɨ�跶Χ����λ����
	double	DetectAng_Pitch;	//	�������ɨ�����Ľǣ���λ����
	double	DetectRange_Pitch;	//	�������ɨ�跶Χ����λ����
	short	Fc;					//	��Ƶ 0��C����(2~4)��1��S����(4~8)
	double	DetectRangeMax;		//	�ο�������Χ����λ����
	bool	Type_MTI;			//	ʹ��MTI
	bool	Type_MTD;			//	ʹ��MTD
};

// �����״�
struct TrackRadar{
	double	Offset_x;			//	�����ָ�ӳ���ƫ��x����λ����
	double	Offset_y;			//	�����ָ�ӳ���ƫ��y����λ����
	double	Offset_z;			//	�����ָ�ӳ���ƫ��z����λ����
	short	RadarType;			//	�״����� 0����е��1��һά�����2����ά�����
	double	DetectAng_Yaw_Start;//	��λ���ɨ�����Ľǿ�ʼ����λ����
	double	DetectAng_Yaw_Stop;	//	��λ���ɨ�����Ľǽ�������λ����
	double	DetectRange_Yaw;	//	��λ���ɨ�跶Χ����λ����
	double	DetectAng_Pitch;	//	�������ɨ�����Ľǣ���λ����
	double	DetectRange_Pitch;	//	�������ɨ�跶Χ����λ����
	short	Fc;					//	��Ƶ 0��Ka����
	double	DetectRangeMax;		//	�ο�������Χ����λ����
	bool	Type_MTI;			//	ʹ��MTI
	bool	Type_MTD;			//	ʹ��MTD
	double	Turn_Az_Vel;		//	��λת�����ٶȣ���λ����/��
	double	Turn_El_Vel;		//	����ת�����ٶȣ���λ����/��
	double	Turn_Az_Acc;		//	��λת���Ǽ��ٶȣ���λ����/��ƽ��
	double	Turn_El_Acc;		//	����ת���Ǽ��ٶȣ���λ����/��ƽ��
	double	Turn_Az_Error;		//	��λ�ŷ����پ��ȣ���λ����
	double	Turn_El_Error;		//	�����ŷ����پ��ȣ���λ����
};

// ������
struct PhotTrack{
	double	Offset_x;					//	�����ָ�ӳ���ƫ��x����λ����
	double	Offset_y;					//	�����ָ�ӳ���ƫ��y����λ����
	double	Offset_z;					//	�����ָ�ӳ���ƫ��z����λ����
	double	DetectAng_Yaw_Start;		//	��λ���ɨ�����Ľǿ�ʼ����λ����
	double	DetectAng_Yaw_Stop;			//	��λ���ɨ�����Ľǽ�������λ����
	double	DetectAngRange_Yaw;			//	��λ���ɨ�跶Χ����λ����
	double	DetectAng_Pitch;			//	�������ɨ�����Ľǣ���λ����
	double	DetectAngRange_Pitch;		//	�������ɨ�跶Χ����λ����
	double	DetectAngSpeedMax_Pitch;	//	�����ٸߵͽ��ٶȣ���λ����/��
	double	DetectAngAccMax_Pitch;		//	�����ٸߵͽǼ��ٶȣ���λ����/��ƽ��
	double	DetectAngSpeedMax_Yaw;		//	�����ٷ�λ���ٶȣ���λ����/��
	double	DetectAngAccMax_Yaw;		//	�����ٷ�λ�Ǽ��ٶȣ���λ����/��ƽ��
	double	DetectRangeMax;				//	������Χ����λ����
	double	ServoPre;					//	�ŷ����پ��ȣ���λ����
	bool	LaserWork;					//	������
	double	LaserDisPre;				//	�����ྫ�ȣ���λ����
};

// �̶���ɻ�
struct FixedWing{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	int jumpToPoint;		//	·�����
	double RCS;				//	RCS, ��λ��ƽ����
	short RCS_Type;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	����, ��λ����
	double Width;			//	��չ, ��λ����
	double Height;			//	����, ��λ����
	bool InterfereFlag;		//	��Դѹ�Ƹ���, 0-�ޣ� 1-��
	double carrierFrequency;//��Ƶ, ��λ���׺���
	double bandwidth;		//����, ��λ���׺���
	double power;			//����, ��λ���ֱ�����
};

// ֱ����
struct Helicopter{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	int jumpToPoint;		//	·�����
	double RCS;				//	RCS, ��λ��ƽ����
	short RCS_Type;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	����, ��λ����
	double Width;			//	��չ, ��λ����
	double Height;			//	����, ��λ����
	bool InterfereFlag;		//	��Դѹ�Ƹ���, 0-�ޣ� 1-��
	double carrierFrequency;//��Ƶ, ��λ���׺���
	double bandwidth;		//����, ��λ���׺���
	double power;			//����, ��λ���ֱ�����
};

// ���˻�
struct UAV{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	int jumpToPoint;		//	·�����
	double RCS;				//	RCS, ��λ��ƽ����
	short RCS_Type;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	����, ��λ����
	double Width;			//	��չ, ��λ����
	double Height;			//	����, ��λ����
	bool InterfereFlag;		//	��Դѹ�Ƹ���, 0-�ޣ� 1-��
	double carrierFrequency;//��Ƶ, ��λ���׺���
	double bandwidth;		//����, ��λ���׺���
	double power;			//����, ��λ���ֱ�����
};

// Ѳ������
struct CruiseMissile{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	int jumpToPoint;		//	·�����
	double RCS;				//	RCS, ��λ��ƽ����
	short RCS_Type;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	����, ��λ����
	double Width;			//	��չ, ��λ����
	double Height;			//	����, ��λ����
};

// ��ȷ�Ƶ�ը��
struct GuidedBomb{
	double lon;				//	����
	double lat;				//	γ��
	double alt;				//	�߶�
	double yaw;				//	��λ��
	double pitch;			//	������
	double roll;			//	��ת��
	int jumpToPoint;		//	·�����
	double RCS;				//	RCS, ��λ��ƽ����
	short RCS_Type;			//	RCS�������, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	����, ��λ����
	double Width;			//	��չ, ��λ����
	double Height;			//	����, ��λ����
};

*/