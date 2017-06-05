mouseHandler(){
	//Info: http://www.computer-engineering.org/ps2mouse/
	//				Bit 7	Bit 6		Bit 5		Bit 4		Bit 3		Bit 2		Bit 1		Bit 0
	//  Byte 1	Y overflow	X overflow	Y sign bit	X sign bit	Always 1	Middle Btn	Right Btn	Left Btn
	//  Byte 2	X movement (Entero)
	//  Byte 3	Y movement (Entero)
	//Int -> 4 Bytes
	//Proceso la informacion
	int info = getMouseInfo();
	int Byte1 = (info >> (8*0)) & 0xff;
	int xmovement = (info >> (8*1)) & 0xff;
	int ymovement = (info >> (8*2)) & 0xff; //Chekear si el que se agrega es el primero o el ultimo
	int yoverflow = ((Byte1 >> 7)  & 0x01);
	int xoverflow = ((Byte1 >> 6)  & 0x01);
	int ysign = ((Byte1 >> 5)  & 0x01);
	int xsign = ((Byte1 >> 4)  & 0x01);
	//int xoverflow = ((Byte1 >> 3)  & 0x01);
	int middleButton = ((Byte1 >> 2)  & 0x01);
	int rightButton = ((Byte1 >> 2)  & 0x01);
	int leftButton = ((Byte1 >> 2)  & 0x01);

	if(rightButton){
		//Click derecho
	}
	if(middleButton){
		//Click central
	}
	if(leftButton){
		//Click izquierdo
	}
	//Mostrar movimientos

}