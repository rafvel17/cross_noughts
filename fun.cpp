#include "framework.h"

int fwinner(int**mas, int x1, int y1, int n)
{
	 int m, i;

/*------------------Победа по горизонтали----------------*/
	 if(x1>4 && x1<n-4)
	 {
		 m = 5;
		 for(i=0; i<m; i++)
		 {
			if(mas[x1-i][y1] == 1 && mas[x1-i+1][y1] == 1 && mas[x1-i+2][y1] == 1 && mas[x1-i+3][y1] == 1 && mas[x1-i+4][y1] == 1)
				return 1;
			else if(mas[x1-i][y1] == 2 && mas[x1-i+1][y1] == 2 && mas[x1-i+2][y1] == 2 && mas[x1-i+3][y1] == 2 && mas[x1-i+4][y1] == 2)
				return 0;
		 }
	 }
	 else 
	 {
		 if(x1<5)
		 {
			m = x1+1;
			for(i=0; i<m; i++)
			{
				if(mas[x1-i][y1] == 1 && mas[x1-i+1][y1] == 1 && mas[x1-i+2][y1] == 1 && mas[x1-i+3][y1] == 1 && mas[x1-i+4][y1] == 1)
					return 1;
				else if(mas[x1-i][y1] == 2 && mas[x1-i+1][y1] == 2 && mas[x1-i+2][y1] == 2 && mas[x1-i+3][y1] == 2 && mas[x1-i+4][y1] == 2)
					return 0;
			}
		 }
		 else 
		 {
			 m = n-x1;
			 for(i=0; i<m; i++)
			 {
				if(mas[x1+i][y1] == 1 && mas[x1+i-1][y1] == 1 && mas[x1+i-2][y1] == 1 && mas[x1+i-3][y1] == 1 && mas[x1+i-4][y1] == 1)
					return 1;
				else if(mas[x1+i][y1] == 2 && mas[x1+i-1][y1] == 2 && mas[x1+i-2][y1] == 2 && mas[x1+i-3][y1] == 2 && mas[x1+i-4][y1] == 2)
					return 0;
			 }
		 }
	 }

/*---------------------Победа по вертикали--------------------*/
	 if(y1>4 && y1<n-4)
	 {
		 m = 5;
		 for(i=0; i<m; i++)
		 {
			if(mas[x1][y1-i] == 1 && mas[x1][y1-i+1] == 1 && mas[x1][y1-i+2] == 1 && mas[x1][y1-i+3] == 1 && mas[x1][y1-i+4] == 1)
				return 1;
			else if(mas[x1][y1-i] == 2 && mas[x1][y1-i+1] == 2 && mas[x1][y1-i+2] == 2 && mas[x1][y1-i+3] == 2 && mas[x1][y1-i+4] == 2)
				return 0;
		 }
	 }
	 else 
	 {
		 if(y1<5)
		 {
			m = y1+1;
			for(i=0; i<m; i++)
			{
				if(mas[x1][y1-i] == 1 && mas[x1][y1-i+1] == 1 && mas[x1][y1-i+2] == 1 && mas[x1][y1-i+3] == 1 && mas[x1][y1-i+4] == 1)
					return 1;
				else if(mas[x1][y1-i] == 2 && mas[x1][y1-i+1] == 2 && mas[x1][y1-i+2] == 2 && mas[x1][y1-i+3] == 2 && mas[x1][y1-i+4] == 2)
					return 0;
			}
		 }
		 else 
		 {
			 m = n-x1;
			 for(i=0; i<m; i++)
			 {
				if(mas[x1][y1+i] == 1 && mas[x1][y1-i+1] == 1 && mas[x1][y1+i-2] == 1 && mas[x1][y1+i-3] == 1 && mas[x1][y1+i-4] == 1)
					return 1;
				else if(mas[x1][y1+i] == 2 && mas[x1][y1-i+1] == 2 && mas[x1][y1+i-2] == 2 && mas[x1][y1+i-3] == 2 && mas[x1][y1+i-4] == 2)
					return 0;
			 }
		 }
	 }

/*-------------------------Победа по главной диогонали--------------------------*/
	 if(x1>4 && x1<n-4)
	 {
		 m = 5;
		 for(i=0; i<m; i++)
		 {
			if(mas[x1-i][y1-i] == 1 && mas[x1-i+1][y1-i+1] == 1 && mas[x1-i+2][y1-i+2] == 1 && mas[x1-i+3][y1-i+3] == 1 && mas[x1-i+4][y1-i+4] == 1)
				 return 1;
			 else if(mas[x1-i][y1-i] == 2 && mas[x1-i+1][y1-i+1] == 2 && mas[x1-i+2][y1-i+2] == 2 && mas[x1-i+3][y1-i+3] == 2 && mas[x1-i+4][y1-i+4] == 2)
				 return 0;
		 }
	 }
	 else 
	 {
		 if(x1<5)
		 {
			m = x1+1;
			for(i=0; i<m; i++)
			{
				if(mas[x1-i][y1-i] == 1 && mas[x1-i+1][y1-i+1] == 1 && mas[x1-i+2][y1-i+2] == 1 && mas[x1-i+3][y1-i+3] == 1 && mas[x1-i+4][y1-i+4] == 1)
					 return 1;
				 else if(mas[x1-i][y1-i] == 2 && mas[x1-i+1][y1-i+1] == 2 && mas[x1-i+2][y1-i+2] == 2 && mas[x1-i+3][y1-i+3] == 2 && mas[x1-i+4][y1-i+4] == 2)
					return 0;
			}
		 }
		 else 
		 {
			 m = n-x1;
			 for(i=0; i<m; i++)
			 {
				 if(mas[x1+i][y1+i] == 1 && mas[x1+i-1][y1+i-1] == 1 && mas[x1+i-2][y1+i-2] == 1 && mas[x1+i-3][y1+i-3] == 1 && mas[x1+i-4][y1+i-4] == 1)
					 return 1;
				 else if(mas[x1+i][y1+i] == 2 && mas[x1+i-1][y1+i-1] == 2 && mas[x1+i-2][y1+i-2] == 2 && mas[x1+i-3][y1+i-3] == 2 && mas[x1+i-4][y1+i-4] == 2)
					 return 0;
			 }
		 }
	 }

/*-------------------------Победа по побочной диогонали--------------------------*/
	 if(x1>4 && x1<n-4)
	 {
		 m = 5;
		 for(i=0; i<m; i++)
		 {
			if(mas[x1-i][y1+i] == 1 && mas[x1-i+1][y1+i-1] == 1 && mas[x1-i+2][y1+i-2] == 1 && mas[x1-i+3][y1+i-3] == 1 && mas[x1-i+4][y1+i-4] == 1)
				return 1;
			else if(mas[x1-i][y1+i] == 2 && mas[x1-i+1][y1+i-1] == 2 && mas[x1-i+2][y1+i-2] == 2 && mas[x1-i+3][y1+i-3] == 2 && mas[x1-i+4][y1+i-4] == 2)
				return 0;
		 }
	 }
	 else 
	 {
		 if(x1<5)
		 {
			m = x1+1;
			for(i=0; i<m; i++)
			{
				if(mas[x1-i][y1+i] == 1 && mas[x1-i+1][y1+i-1] == 1 && mas[x1-i+2][y1+i-2] == 1 && mas[x1-i+3][y1+i-3] == 1 && mas[x1-i+4][y1+i-4] == 1)
					return 1;
				 else if(mas[x1-i][y1+i] == 2 && mas[x1-i+1][y1+i-1] == 2 && mas[x1-i+2][y1+i-2] == 2 && mas[x1-i+3][y1+i-3] == 2 && mas[x1-i+4][y1+i-4] == 2)
					 return 0;
			}
		 }
		 else 
		 {
			 m = n-x1;
			 for(i=0; i<m; i++)
			 {
				 if(mas[x1+i][y1-i] == 1 && mas[x1+i-1][y1-i+1] == 1 && mas[x1+i-2][y1-i+2] == 1 && mas[x1+i-3][y1-i+3] == 1 && mas[x1+i-4][y1-i+4] == 1)
					return 1;
				 else if(mas[x1+i][y1-i] == 2 && mas[x1+i-1][y1-i+1] == 2 && mas[x1+i-2][y1-i+2] == 2 && mas[x1+i-3][y1-i+3] == 2 && mas[x1+i-4][y1-i+4] == 2)
					 return 0;
			 }
		 }
	 }

	return 2;
}
