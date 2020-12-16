#include"Error.h"
namespace Error {
	//����� ������: 0 - 99 - ��������� ������
	//				100 - 109 - ������ ����������
	//				110 - 119 - ������ �������� � ������ ������
	//				500 - 599 - ������ � ����������� �����������
	//				600 - 699 - ������ � �������������� �����������
	//				700 - 799 - ������ � ������������� �����������
	ERROR errors[ERROR_MAX_ENTRY] =
	{	//������� ������
	ERROR_ENTRY(0,"������������ ��� ������"),	//��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
	ERROR_ENTRY(1,"��������� ����"),
	ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100,"�������� -in ������ ���� �����"),
	ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104,"��������� ����� �������� ���������"),
	ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110,"������ ��� �������� ����� � �������� ����� (-in)"),
	ERROR_ENTRY(111,"������������ ������ � �������� ����� (-in)"),
	ERROR_ENTRY(112,"������ ��� �������� ����� ��������� (-log)"),
	ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
	ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),
	ERROR_ENTRY(500,"�� ���������� ����� �����"),
	ERROR_ENTRY(501,"��������� ���������� ������� �����"),
	ERROR_ENTRY(502,"�� ������� ��������� �������"),
	ERROR_ENTRY(503,"��� ������� ���� ��������������"),
	ERROR_ENTRY(504,"������������ ����� ��������������"),
	ERROR_ENTRY(505,"������������� �������������������� ���������� ��� �������"),
	ERROR_ENTRY_NODEF(506),ERROR_ENTRY_NODEF(507),ERROR_ENTRY_NODEF(508), ERROR_ENTRY_NODEF(509),
	ERROR_ENTRY_NODEF10(510), ERROR_ENTRY_NODEF10(520), ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540),
	ERROR_ENTRY_NODEF10(550), ERROR_ENTRY_NODEF10(560), ERROR_ENTRY_NODEF10(570), ERROR_ENTRY_NODEF10(580),
	ERROR_ENTRY_NODEF10(590),
	ERROR_ENTRY(600,"������������ ��������� ���������"),
	ERROR_ENTRY(601,"��������� ��������"),
	ERROR_ENTRY(602,"������ � ���������"),
	ERROR_ENTRY(603,"������ � ����������� ������"),
	ERROR_ENTRY(604,"������ � ���������� ��������� �������"),
	ERROR_ENTRY(605,"������ � ���������� ���������� �������"),
	ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(608),	ERROR_ENTRY_NODEF(609),
	ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
	ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), 
	ERROR_ENTRY_NODEF10(690),
	ERROR_ENTRY(700,"������������ ����� ���������� �������"),
	ERROR_ENTRY(701,"������������ ���������� ���������� �������"),
	ERROR_ENTRY(702,"���������� ��������� �� ���������������� ����"),
	ERROR_ENTRY(703,"������� ���������� �������� ���"),
	ERROR_ENTRY(704,"����� ������� �� ������� �����������"),
	ERROR_ENTRY(705,"������ � ������ ���� ch '.'"),
	ERROR_ENTRY_NODEF(706),ERROR_ENTRY_NODEF(707), ERROR_ENTRY_NODEF(708),	ERROR_ENTRY_NODEF(709),
	ERROR_ENTRY_NODEF10(710),
	ERROR_ENTRY_NODEF10(720), ERROR_ENTRY_NODEF10(730), ERROR_ENTRY_NODEF10(740), ERROR_ENTRY_NODEF10(750),
	ERROR_ENTRY_NODEF10(760), ERROR_ENTRY_NODEF10(770), ERROR_ENTRY_NODEF10(780), ERROR_ENTRY_NODEF10(790),
	ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR getError(int id) {
		if (id >= 0 && id < ERROR_MAX_ENTRY)
			return errors[id];
		return errors[0];
	}
	ERROR getErrorIn(int id, int line = -1, int column = -1) {
		if (id >= 0 && id < ERROR_MAX_ENTRY) {
			errors[id].inext.line = line;
			errors[id].inext.column = column;

			return errors[id];
		}
		return errors[0];
	}
};