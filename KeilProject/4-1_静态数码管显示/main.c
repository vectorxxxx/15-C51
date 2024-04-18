#include <REGX52.H>

// 0
// dp g f e d c b a
// 0	0	1	1	1	1	1	1
// 0x3F

// 1
// dp g f e d c b a
// 0	0	0	0	0	1	1	0
// 0x06

// 2
// dp g f e d c b a
// 0	1	0	1	1	0	1	1
// 0x5B

// 3
// dp g f e d c b a
// 0	1	0	0	1	1	1	1
// 0x4F

// 4
// dp g f e d c b a
// 0	1	1	0	0	1	1	0
// 0x66

// 5
// dp g f e d c b a
// 0	1	1	0	1	1	0	1
// 0x6D

// 6
// dp g f e d c b a
// 0	1	1	1	1	1	0	1
// 0x7D

// 7
// dp g f e d c b a
// 0	0	0	0	0	1	1	1
// 0x07

// 8
// dp g f e d c b a
// 0	1	1	1	1	1	1	1
// 0x7F

// 9
// dp g f e d c b a
// 0	1	1	0	1	1	1	1
// 0x6F

unsigned char NixieTable[] = {
	0x3f, 
	0x06, 
	0x5b, 
	0x4f, 
	0x66,
	0x6d, 
	0x7d, 
	0x07, 
	0x7f, 
	0x6f
};

void Nixie(unsigned char Location, Number)
{
	switch(Location)
	{
		// 1 => LED8 => Y7 => 111
		case 1: P2_4=1; P2_3=1; P2_2=1; break;
		// 2 => LED7 => Y6 => 110
		case 2: P2_4=1; P2_3=1; P2_2=0; break;
		// 3 => LED6 => Y5 => 101
		case 3: P2_4=1; P2_3=0; P2_2=1; break;
		// 4 => LED5 => Y4 => 100
		case 4: P2_4=1; P2_3=0; P2_2=0; break;
		// 5 => LED4 => Y3 => 011
		case 5: P2_4=0; P2_3=1; P2_2=1; break;
		// 6 => LED3 => Y2 => 010
		case 6: P2_4=0; P2_3=1; P2_2=0; break;
		// 7 => LED2 => Y1 => 001
		case 7: P2_4=0; P2_3=0; P2_2=1; break;
		// 8 => LED1 => Y0 => 000
		case 8: P2_4=0; P2_3=0; P2_2=0; break;
		default: break;
	}

	P0=NixieTable[Number];
}


void main()
{			
	//Nixie(7, 2);
	Nixie(2, 3);
	while(1)
	{
		
	}
}