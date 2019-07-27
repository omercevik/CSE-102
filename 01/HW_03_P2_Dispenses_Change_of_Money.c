#include <stdio.h>

int dispenseChange(double paid, double due, int *tl1, int *krs50, int *krs25, int *krs10, int *krs5, int *krs1);

int main()
{
	double paid = 5, due = 3.75;
	int tl1,krs50,krs25,krs10,krs5,krs1;
	
	if(dispenseChange(paid,due,&tl1,&krs50, &krs25, &krs10, &krs5, &krs1)) /* returns 1 */
		printf("Change: 1TL:%d, Kurus-50:%d,25:%d,10:%d,5:%d,1:%d\n",tl1,krs50,krs25,krs10,krs5,krs1);
	else
		printf("Unable to dispense change.");
	
	return 0;
}

int dispenseChange(double paid, double due, int *tl1, int *krs50, int *krs25, int *krs10, int *krs5, int *krs1)
{
	int dispense;
	dispense = (paid - due)*100;
	
	if( (dispense == dispense/100) || dispense < 0 || paid < 0 || due < 0 )
	{
		return 0;
	}
	else
		*tl1 = dispense/100;
		dispense -= *tl1 * 100;
		*krs50 = dispense/50;
		dispense -= *krs50*50;
		*krs25 = dispense/25;
		dispense -= *krs25*25;
		*krs10 = dispense/10;
		dispense -= *krs10*10;
		*krs5 = dispense/5;
		dispense -= *krs5*5;
		*krs1 = dispense;
		
	return 1;

}
