#include "common.h"
#include "include.h"

char *goodsUnit[6] = {"��", "��", "��", "����", " ֧", "̨"};
char *goodsKind1[6] = {"����", "ͼ��", "����", "����", "�ջ�", "�ҵ�"};
char *goodsKind2[6][3] = {{"����ñ", "ţ�п�", "�ͱ�����" },
                          {"������ͯ����", " �����ݽṹ��", "���»��ֵ䡷"},
                          {"�ֻ�","���","ƽ�����"},
                          {"�з","�㽶","�ײ�"},
                          {"ϴ��¶","����˪","����"},
                          {"���ӻ�","ϴ�»�","�����"}};

char *area[6] = {"�й�", "�ձ�", "Ӣ��", "����", "����", "���ô�"};

void goodsPrint(uint16 sum1, uint16 sum2)
{
	printf("�˿͹������Ʒ��:\n");
	for (int i = 0; i < msgStack.sp; i++)
	{
		msgStack.mem[i].EPC.goods.number=RANGE(msgStack.mem[i].EPC.goods.number,100,1);
		msgStack.mem[i].EPC.goods.floor=RANGE(msgStack.mem[i].EPC.goods.floor,5,1);
		msgStack.mem[i].EPC.goods.area=RANGE(msgStack.mem[i].EPC.goods.area,5,0);
		msgStack.mem[i].EPC.goods.grade=RANGE(msgStack.mem[i].EPC.goods.grade,5,1);
		msgStack.mem[i].EPC.goods.kind1=RANGE(msgStack.mem[i].EPC.goods.kind1,5,0);
		msgStack.mem[i].EPC.goods.kind2=RANGE(msgStack.mem[i].EPC.goods.kind2,2,0);
		printf("��%3d �Ż��� %d �㡿\n", msgStack.mem[i].EPC.goods.number,
			   msgStack.mem[i].EPC.goods.floor);
		printf("����%s��%d�Ǽ���Ʒ:\n",area[msgStack.mem[i].EPC.goods.area],msgStack.mem[i].EPC.goods.grade);
		printf("%s:%s x1 %s ",goodsKind1[msgStack.mem[i].EPC.goods.kind1],
			   goodsKind2[msgStack.mem[i].EPC.goods.kind1][msgStack.mem[i].EPC.goods.kind2],
			   goodsUnit[msgStack.mem[i].EPC.goods.kind1]
				   );
		printf("�ۼ�Ϊ:%.2f Ԫ\n", msgStack.mem[i].EPC.goods.price1 + msgStack.mem[i].EPC.goods.price2 * 0.1);
		printf("------------------------------------------\n");
	}
	printf("�ܼƣ�%.2fԪ\n", sum1 + sum2 * 0.1);
	printf("֧�����!\n");
}
