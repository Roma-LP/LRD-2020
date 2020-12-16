#include"Error.h"
namespace Error {
	//ñåğèè îøèáîê: 0 - 99 - ñèñòåìíûå îøèáêè
	//				100 - 109 - îøèáêè ïàğàìåòğîâ
	//				110 - 119 - îøèáêè îòêğûòèÿ è ÷òåíèÿ ôàéëîâ
	//				500 - 599 - îøèáêè â ëåêñè÷åñêîì àíàëèçàòîğå
	//				600 - 699 - îøèáêè â ñèíòàêñè÷åñêîì àíàëèçàòîğå
	//				700 - 799 - îøèáêè â ñåìàíòè÷åñêîì àíàëèçàòîğå
	ERROR errors[ERROR_MAX_ENTRY] =
	{	//òàáëèöà îøèáîê
	ERROR_ENTRY(0,"Íåäîïóñòèìûé êîä îøèáêè"),	//êîä îøèáêè âíå äèàïàçîíà 0 - ERROR_MAX_ENTRY
	ERROR_ENTRY(1,"Ñèñòåìíûé ñáîé"),
	ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
	ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
	ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
	ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
	ERROR_ENTRY(100,"Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
	ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
	ERROR_ENTRY(104,"Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà"),
	ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
	ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
	ERROR_ENTRY(110,"Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
	ERROR_ENTRY(111,"Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
	ERROR_ENTRY(112,"Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)"),
	ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
	ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
	ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
	ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
	ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),
	ERROR_ENTRY(500,"Íå îáíàğóæåíà òî÷êà âõîäà"),
	ERROR_ENTRY(501,"Ïğåâûøåíî êîëè÷åñòâî âõîäíûõ òî÷åê"),
	ERROR_ENTRY(502,"Íå óäàëîñü ğàçîáğàòü ëåêñåìó"),
	ERROR_ENTRY(503,"Èìÿ ôóíêöèè áûëî ïğîäóáëèğîâàíî"),
	ERROR_ENTRY(504,"Äóáëèğîâàíèå èìåíè èäåíòèôèêàòîğà"),
	ERROR_ENTRY(505,"Èñïîëüçîâàíèå íåèíèöèàëèçèğîâàííîé ïåğåìåííîé èëè ôóíêöèè"),
	ERROR_ENTRY_NODEF(506),ERROR_ENTRY_NODEF(507),ERROR_ENTRY_NODEF(508), ERROR_ENTRY_NODEF(509),
	ERROR_ENTRY_NODEF10(510), ERROR_ENTRY_NODEF10(520), ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540),
	ERROR_ENTRY_NODEF10(550), ERROR_ENTRY_NODEF10(560), ERROR_ENTRY_NODEF10(570), ERROR_ENTRY_NODEF10(580),
	ERROR_ENTRY_NODEF10(590),
	ERROR_ENTRY(600,"Íåïğàâèëüíàÿ ñòğóêòóğà ïğîãğàììû"),
	ERROR_ENTRY(601,"Îøèáî÷íûé îïåğàòîğ"),
	ERROR_ENTRY(602,"Îøèáêà â âûğàæåíèè"),
	ERROR_ENTRY(603,"Îøèáêà â ğàññòàíîâêå çíàêîâ"),
	ERROR_ENTRY(604,"Îøèáêà â ïàğàìåòğàõ ïğîòîòèïà ôóíêöèè"),
	ERROR_ENTRY(605,"Îøèáêà â ïàğàìåòğàõ âûçûâàåìîé ôóíêöèè"),
	ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(608),	ERROR_ENTRY_NODEF(609),
	ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
	ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), 
	ERROR_ENTRY_NODEF10(690),
	ERROR_ENTRY(700,"Íåñîâïàäåíèå òèïîâ ïàğàìåòğîâ ôóíêöèè"),
	ERROR_ENTRY(701,"Íåñîâïàäåíèå êîëè÷åñòâà ïàğàìåòğîâ ôóíêöèè"),
	ERROR_ENTRY(702,"Ïğèñâîåíèå àğãóìåíòó íå ñîîòâåòñòâóşùåãî òèïà"),
	ERROR_ENTRY(703,"Ôóíêöèÿ âîçâğàùàåò íåâåğíûé òèï"),
	//ERROR_ENTRY(704,"×èñëî âûõîäèò çà ãğàíèöû äîïóñòèìîãî"),
	ERROR_ENTRY(704,"Îøèáêà â çàïèñè òèïà ch '.'"),
	ERROR_ENTRY(705,"ßâíàÿ ïîïûòêà äåëåíèÿ íà íóëü"),
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