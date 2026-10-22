#include "LevelTable.h"

// レベルに応じた最大経験値を返す関数
float GetMaxExpForLevel(LEVEL_NUMBER level)
{
	switch (level)
	{
	case LEVEL_1:
		return 10.0000f;
	case LEVEL_2:
		return 10.5000f;
	case LEVEL_3:
		return 11.0250f;
	case LEVEL_4:
		return 11.5763f;
	case LEVEL_5:
		return 12.1551f;
	case LEVEL_6:
		return 12.7628f;
	case LEVEL_7:
		return 13.4010f;
	case LEVEL_8:
		return 14.0710f;
	case LEVEL_9:
		return 14.7746f;
	case LEVEL_10:
		return 15.5133f;
	case LEVEL_11:
		return 17.0646f;
	case LEVEL_12:
		return 18.7711f;
	case LEVEL_13:
		return 20.6482f;
	case LEVEL_14:
		return 22.7130f;
	case LEVEL_15:
		return 24.9843f;
	case LEVEL_16:
		return 27.4827f;
	case LEVEL_17:
		return 30.2310f;
	case LEVEL_18:
		return 33.2541f;
	case LEVEL_19:
		return 36.5795f;
	case LEVEL_20:
		return 40.2375f;
	case LEVEL_21:
		return 46.2731f;
	case LEVEL_22:
		return 53.2140f;
	case LEVEL_23:
		return 61.1961f;
	case LEVEL_24:
		return 70.3756f;
	case LEVEL_25:
		return 80.9319f;
	case LEVEL_26:
		return 93.0717f;
	case LEVEL_27:
		return 107.0324f;
	case LEVEL_28:
		return 123.0873f;
	case LEVEL_29:
		return 141.5504f;
	case LEVEL_30:
		return 162.7830f;
	case LEVEL_31:
		return 195.3396f;
	case LEVEL_32:
		return 234.4075f;
	case LEVEL_33:
		return 281.2890f;
	case LEVEL_34:
		return 337.5468f;
	case LEVEL_35:
		return 405.0561f;
	case LEVEL_36:
		return 486.0673f;
	case LEVEL_37:
		return 583.2808f;
	case LEVEL_38:
		return 699.9369f;
	case LEVEL_39:
		return 839.9243f;
	case LEVEL_40:
		return 1007.9092f;
	case LEVEL_41:
		return 1259.8865f;
	case LEVEL_42:
		return 1574.8581f;
	case LEVEL_43:
		return 1968.5726f;
	case LEVEL_44:
		return 2460.7158f;
	case LEVEL_45:
		return 3075.8948f;
	case LEVEL_46:
		return 3844.8685f;
	case LEVEL_47:
		return 4806.0856f;
	case LEVEL_48:
		return 6007.6070f;
	case LEVEL_49:
		return 7509.5087f;
	case LEVEL_50:
		return 9386.8859f;
	case LEVEL_51:
		return 12202.9516f;
	case LEVEL_52:
		return 15863.8371f;
	case LEVEL_53:
		return 20622.9882f;
	case LEVEL_54:
		return 26809.8847f;
	case LEVEL_55:
		return 34852.8501f;
	case LEVEL_56:
		return 45308.7052f;
	case LEVEL_57:
		return 58901.3167f;
	case LEVEL_58:
		return 76571.7117f;
	case LEVEL_59:
		return 99543.2253f;
	case LEVEL_60:
		return 129406.1928f;
	case LEVEL_61:
		return 174698.3603f;
	case LEVEL_62:
		return 235842.7865f;
	case LEVEL_63:
		return 318387.7617f;
	case LEVEL_64:
		return 429823.4783f;
	case LEVEL_65:
		return 580261.6957f;
	case LEVEL_66:
		return 783353.2893f;
	case LEVEL_67:
		return 1057526.9405f;
	case LEVEL_68:
		return 1427661.3697f;
	case LEVEL_69:
		return 1927342.8491f;
	case LEVEL_70:
		return 2601912.8462f;
	case LEVEL_71:
		return 3642677.9847f;
	case LEVEL_72:
		return 5099749.1786f;
	case LEVEL_73:
		return 7139648.8500f;
	case LEVEL_74:
		return 9995508.3900f;
	case LEVEL_75:
		return 13993711.7460f;
	case LEVEL_76:
		return 19591196.4445f;
	case LEVEL_77:
		return 27427675.0222f;
	case LEVEL_78:
		return 38398745.0311f;
	case LEVEL_79:
		return 53758243.0436f;
	case LEVEL_80:
		return 75261540.2611f;
	case LEVEL_81:
		return 109129233.3785f;
	case LEVEL_82:
		return 158237388.3989f;
	case LEVEL_83:
		return 229444213.1784f;
	case LEVEL_84:
		return 332694109.1086f;
	case LEVEL_85:
		return 482406458.2075f;
	case LEVEL_86:
		return 699489364.4009f;
	case LEVEL_87:
		return 1014259578.3812f;
	case LEVEL_88:
		return 1470676388.6528f;
	case LEVEL_89:
		return 2132480763.5465f;
	case LEVEL_90:
		return 3092097107.1425f;
	case LEVEL_91:
		return 4638145660.7137f;
	case LEVEL_92:
		return 6957218491.0706f;
	case LEVEL_93:
		return 10435827736.6059f;
	case LEVEL_94:
		return 15653741604.9088f;
	case LEVEL_95:
		return 23480612407.3633f;
	case LEVEL_96:
		return 35220918611.0449f;
	case LEVEL_97:
		return 52831377916.5674f;
	case LEVEL_98:
		return 79247066874.8510f;
	case LEVEL_99:
		return 118870600312.2766f;
	default:
		return 0.0f; // Default to level 1 if invalid level
	}
}
	
	
LEVEL_NUMBER GetNextLevel(LEVEL_NUMBER currentLevel) {
	switch (currentLevel)
	{
	case LEVEL_1: return LEVEL_2;
	case LEVEL_2: return LEVEL_3;
	case LEVEL_3: return LEVEL_4;
	case LEVEL_4: return LEVEL_5;
	case LEVEL_5: return LEVEL_6;
	case LEVEL_6: return LEVEL_7;
	case LEVEL_7: return LEVEL_8;
	case LEVEL_8: return LEVEL_9;
	case LEVEL_9: return LEVEL_10;
	case LEVEL_10: return LEVEL_11;
	case LEVEL_11: return LEVEL_12;
	case LEVEL_12: return LEVEL_13;
	case LEVEL_13: return LEVEL_14;
	case LEVEL_14: return LEVEL_15;
	case LEVEL_15: return LEVEL_16;
	case LEVEL_16: return LEVEL_17;
	case LEVEL_17: return LEVEL_18;
	case LEVEL_18: return LEVEL_19;
	case LEVEL_19: return LEVEL_20;
	case LEVEL_20: return LEVEL_21;
	case LEVEL_21: return LEVEL_22;
	case LEVEL_22: return LEVEL_23;
	case LEVEL_23: return LEVEL_24;
	case LEVEL_24: return LEVEL_25;
	case LEVEL_25: return LEVEL_26;
	case LEVEL_26: return LEVEL_27;
	case LEVEL_27: return LEVEL_28;
	case LEVEL_28: return LEVEL_29;
	case LEVEL_29: return LEVEL_30;
	case LEVEL_30: return LEVEL_31;
	case LEVEL_31: return LEVEL_32;
	case LEVEL_32: return LEVEL_33;
	case LEVEL_33: return LEVEL_34;
	case LEVEL_34: return LEVEL_35;
	case LEVEL_35: return LEVEL_36;
	case LEVEL_36: return LEVEL_37;
	case LEVEL_37: return LEVEL_38;
	case LEVEL_38: return LEVEL_39;
	case LEVEL_39: return LEVEL_40;
	case LEVEL_40: return LEVEL_41;
	case LEVEL_41: return LEVEL_42;
	case LEVEL_42: return LEVEL_43;
	case LEVEL_43: return LEVEL_44;
	case LEVEL_44: return LEVEL_45;
	case LEVEL_45: return LEVEL_46;
	case LEVEL_46: return LEVEL_47;
	case LEVEL_47: return LEVEL_48;
	case LEVEL_48: return LEVEL_49;
	case LEVEL_49: return LEVEL_50;
	case LEVEL_50: return LEVEL_51;
	case LEVEL_51: return LEVEL_52;
	case LEVEL_52: return LEVEL_53;
	case LEVEL_53: return LEVEL_54;
	case LEVEL_54: return LEVEL_55;
	case LEVEL_55: return LEVEL_56;
	case LEVEL_56: return LEVEL_57;
	case LEVEL_57: return LEVEL_58;
	case LEVEL_58: return LEVEL_59;
	case LEVEL_59: return LEVEL_60;
	case LEVEL_60: return LEVEL_61;
	case LEVEL_61: return LEVEL_62;
	case LEVEL_62: return LEVEL_63;
	case LEVEL_63: return LEVEL_64;
	case LEVEL_64: return LEVEL_65;
	case LEVEL_65: return LEVEL_66;
	case LEVEL_66: return LEVEL_67;
	case LEVEL_67: return LEVEL_68;
	case LEVEL_68: return LEVEL_69;
	case LEVEL_69: return LEVEL_70;
	case LEVEL_70: return LEVEL_71;
	case LEVEL_71: return LEVEL_72;
	case LEVEL_72: return LEVEL_73;
	case LEVEL_73: return LEVEL_74;
	case LEVEL_74: return LEVEL_75;
	case LEVEL_75: return LEVEL_76;
	case LEVEL_76: return LEVEL_77;
	case LEVEL_77: return LEVEL_78;
	case LEVEL_78: return LEVEL_79;
	case LEVEL_79: return LEVEL_80;
	case LEVEL_80: return LEVEL_81;
	case LEVEL_81: return LEVEL_82;
	case LEVEL_82: return LEVEL_83;
	case LEVEL_83: return LEVEL_84;
	case LEVEL_84: return LEVEL_85;
	case LEVEL_85: return LEVEL_86;
	case LEVEL_86: return LEVEL_87;
	case LEVEL_87: return LEVEL_88;
	case LEVEL_88: return LEVEL_89;
	case LEVEL_89: return LEVEL_90;
	case LEVEL_90: return LEVEL_91;
	case LEVEL_91: return LEVEL_92;
	case LEVEL_92: return LEVEL_93;
	case LEVEL_93: return LEVEL_94;
	case LEVEL_94: return LEVEL_95;
	case LEVEL_95: return LEVEL_96;
	case LEVEL_96: return LEVEL_97;
	case LEVEL_97: return LEVEL_98;
	case LEVEL_98: return LEVEL_99;
	case LEVEL_99: return LEVEL_MAX;
	default: return currentLevel; // マックスならそのまま
	}
};