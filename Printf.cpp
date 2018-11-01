#include <stdio.h>
#include <stdarg.h>

//Zaimplemetnowac uproszczonej funkcji "Printf": %c, %d, %f, %s oraz zmienia ` na '

int Printf(const char* sFormat, ...);
int Printfv(const char* sFormat, va_list va_list);

void outDec(int x); // znakowo wypisuje liczbe calkowita
void outNum(int x); //wypisuje liczbe wieksza od  zera
void outDouble(double x); // wypisuje znakowo liczbe dobule
void outChar(char c); // wypisuje znak
void outStr(char* str);//wypisuje znakowo string



int main(int argc, char* argv[])
{
	int n = -0;
	char c = '$';
	double x = 12000000.34500000012;
	double y = -.12;
	double z = -1.5;
	const char* str = "To jest string";

	Printf("str=%s\n%f%c   n=%d \\ \% /\ny=%f   z=%f\n\n", str, x, c, n, y, z);
	return 0;
}




//----------------------------------
int Printf(const char* sFormat, ...)
{
	
	va_list args;//args - pointer to list of arguments
	va_start(args, sFormat);// initialize variable arguments
	int res = Printfv(sFormat, args);
	va_end(args);
	return res;

}
//----------------------------------
int Printfv(const char* sFormat, va_list va_list)
{
	char c;
	while (c = *sFormat++)
	{
		//funkcja pobierajaca kolejny element z listy argumentow
		switch (c)
		{
		case '%':
			switch (c = *sFormat++)
			{
			case'c': outChar(va_arg(va_list, char));		break;
			case's': outStr(va_arg(va_list, char*));		break;
			case'd': outDec(va_arg(va_list, int));			break;
			case'f': outDouble(va_arg(va_list, double));	break;
			default: outChar('%'); outChar(c);				break;
			}
			break;
		case '`': c = '\'';//wypisać '
		default: outChar(c);
		}
	}
	return 1;
}



//----------------------------------
void outDec(int x)
{
	if (x < 0)
	{
		outChar('-');
		x = -x;
	}
	else if (!x)
	{
		outChar('0');
		return;
	}
	outNum(x);
}
//----------------------------------
void outNum(int x)
{
	if (x > 0)
	{
		outNum(x / 10);
		outChar(x % 10 + '0');
	}
}
//----------------------------------
void outDouble(double x)
{
	if (x < 0)
	{
		outChar('-');
		x = -x;
	}

	if (x == 0) outChar('0');
	outDec((int)x);
	outChar('.');
	x = x - (int)x;
	for (int i = 0; i < 6 && (x - (int)x) > 1e-6; i++)
	{
		x *= 10;
		outChar((int)x % 10 + '0');
	}
}
//----------------------------------
void outChar(char c)
{
	putchar(c);
}
//----------------------------------
void outStr(char* str)
{
	while (*str != 0)
		outChar(*str++);
}
//----------------------------------