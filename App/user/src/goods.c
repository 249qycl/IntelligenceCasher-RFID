#include "common.h"
#include "include.h"

char *goodsUnit[6] = {"件", "本", "部", "公斤", " 支", "台"};
char *goodsKind1[6] = {"服饰", "图书", "数码", "生鲜", "日化", "家电"};
char *goodsKind2[6][3] = {{"遮阳帽", "牛仔裤", "劳保手套" },
                          {"《格林童话》", " 《数据结构》", "《新华字典》"},
                          {"手机","相机","平板电脑"},
                          {"螃蟹","香蕉","白菜"},
                          {"洗发露","护手霜","牙膏"},
                          {"电视机","洗衣机","电冰箱"}};

char *area[6] = {"中国", "日本", "英国", "韩国", "美国", "加拿大"};

void goodsPrint(uint16 sum1, uint16 sum2)
{
	printf("顾客购买的商品有:\n");
	for (int i = 0; i < msgStack.sp; i++)
	{
		msgStack.mem[i].EPC.goods.number=RANGE(msgStack.mem[i].EPC.goods.number,100,1);
		msgStack.mem[i].EPC.goods.floor=RANGE(msgStack.mem[i].EPC.goods.floor,5,1);
		msgStack.mem[i].EPC.goods.area=RANGE(msgStack.mem[i].EPC.goods.area,5,0);
		msgStack.mem[i].EPC.goods.grade=RANGE(msgStack.mem[i].EPC.goods.grade,5,1);
		msgStack.mem[i].EPC.goods.kind1=RANGE(msgStack.mem[i].EPC.goods.kind1,5,0);
		msgStack.mem[i].EPC.goods.kind2=RANGE(msgStack.mem[i].EPC.goods.kind2,2,0);
		printf("【%3d 号货架 %d 层】\n", msgStack.mem[i].EPC.goods.number,
			   msgStack.mem[i].EPC.goods.floor);
		printf("产自%s的%d星级产品:\n",area[msgStack.mem[i].EPC.goods.area],msgStack.mem[i].EPC.goods.grade);
		printf("%s:%s x1 %s ",goodsKind1[msgStack.mem[i].EPC.goods.kind1],
			   goodsKind2[msgStack.mem[i].EPC.goods.kind1][msgStack.mem[i].EPC.goods.kind2],
			   goodsUnit[msgStack.mem[i].EPC.goods.kind1]
				   );
		printf("售价为:%.2f 元\n", msgStack.mem[i].EPC.goods.price1 + msgStack.mem[i].EPC.goods.price2 * 0.1);
		printf("------------------------------------------\n");
	}
	printf("总计：%.2f元\n", sum1 + sum2 * 0.1);
	printf("支付完成!\n");
}
