#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <stdint.h>
#define N 2048

typedef struct{       //定义一个结构体表示复数的类型
	float real;
	float imag;
}complex;

complex x[N], *W;   //定义输入序列和旋转因子
int size=0;   //定义数据长度
float PI=4.0*atan(1); //定义π 因为tan(π/4)=1 所以arctan（1）*4=π，增加π的精度

void readFile() {
    FILE *file = fopen("/home/g/riscv/gem5/tests/fft_test/in.txt", "r");
    if (!file) {
        perror("文件打开失败");
        return;
    }

	// 读取文件并赋值给复数数组
    int i = 0;
    while (fscanf(file, "%f%f", &x[i].real, &x[i].imag) == 2) {//%lf则是读取double类型  %f为float类型,%d为整数型
        i++;
    }
	size = i;
    fclose(file);

    printf("读取到 %d 个复数数据\n", size);
}

void output()
{
	FILE *outfile = fopen("/home/g/riscv/gem5/tests/fft_test/out.txt","w");
	if (!outfile) {
        perror("文件打开失败");
        return;
    }
	int i;
	// // 保存复数的实部和虚部
    // for (int i = 0; i < size; i++) {
    //     fprintf(file, "%.2f %.2f\n", x[i].real/sqrt(size), x[i].imag/sqrt(size));
    // }

	for(i=0;i<size;i++){
		fprintf(outfile,"%.4f",x[i].real);///sqrt(N)
		if(x[i].imag>=0)
		{
			fprintf(outfile,"+%.4fj\n",x[i].imag);
		}
		else if(fabs(x[i].imag)<0)
		{
			fprintf(outfile,"\n");
		}
		else
		{
			fprintf(outfile,"%.4fj\n",x[i].imag);
		}
	}
	fclose(outfile);
    printf("傅里叶变换结果已保存到文件：\n");
}

void change()
{
	complex temp;
	unsigned short i=0,j=0,k=0;
	float t;
	t=(log(size)/log(2));
	for(i=0;i<size;i++)
	{
		k=i;
		j=0;
		while( (t--)>0 )
		{
			j=j<<1;
			j|=(k & 1);
			k=k>>1;
		}
		if(j>i)
		{
			temp=x[i];
			x[i]=x[j];
			x[j]=temp;
		}
	}
	// output();
}

void transform()
{
	int i;
	W=(complex *)malloc(sizeof(complex) * size);
	for(i=0;i<size;i++)
	{
		W[i].real=cos(2*PI/size*i);
		W[i].imag=-1*sin(2*PI/size*i);
	}
}

void add(complex a,complex b,complex *c)
{
	c->real=a.real+b.real;
	c->imag=a.imag+b.imag;
}

void sub(complex a,complex b,complex *c)
{
	c->real=a.real-b.real;
	c->imag=a.imag-b.imag;
}

void mul(complex a,complex b,complex *c)
{
	c->real=a.real*b.real - a.imag*b.imag;
	c->imag=a.real*b.imag + a.imag*b.real;
}

void fft()
{
	int i=0,j=0,k=0,m=0;
	complex q,y,z;
	change();
	for(i=0;i<log(size)/log(2) ;i++)
	{
		m=1<<i;
		for(j=0;j<size;j+=2*m)
		{
			for(k=0;k<m;k++)
			{
				mul(x[k+j+m],W[size*k/2/m],&q);
				add(x[j+k],q,&y);
				sub(x[j+k],q,&z);
				x[j+k]=y;
				x[j+k+m]=z;
			}
		}
	}
}

int main()
{
	readFile();

	int i;
	// printf("输入数据的实部、虚部\n");
	// for(i=0;i<size;i++)
	// {
	// 	scanf("%lf%lf",&x[i].real,&x[i].imag);  //输入复数的实部和虚部
	// }
	transform();//变换序列顺序
	fft();//蝶形运算
	output();//输出结果
	return 0;
}