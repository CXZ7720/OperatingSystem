#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};

LIST_HEAD(birthday_list);

struct birthday *createBirthday(int day, int month, int year) {
  struct birthday *person;
  /* TODO: 생일을 위한 메모리를 할당하고, 인자들을 채워 생일을 완성하세요. */
  person = kmalloc(sizeof(*person), GFP_KERNEL);
  person->day = day;
  person->month = month;
  person->year = year;
  //
  return person;
}

int simple_init(void) {
  struct birthday *node1;
  struct birthday *node2;
  struct birthday *node3;
  struct birthday *node4;

  node1 = createBirthday(1,2,2019);
  node2 = createBirthday(2,2,2019);
  node3 = createBirthday(3,2,2019);
  node4 = createBirthday(4,2,2019);

  printk("Loading Module: BDLIST......");
  /* TODO: 생일 목록을 하나씩 생성하는대로 연결리스트에 연결시키세요(노드 삽입). */
  struct birthday *cursor;
  list_add_tail(&node1->list, &birthday_list);
  list_add_tail(&node2->list, &birthday_list);
  list_add_tail(&node3->list, &birthday_list);
  list_add_tail(&node4->list, &birthday_list);

  /* TODO: 완성된 연결리스트를 탐색하는 커널 함수를 사용하여 출력하세요. */
  list_for_each_entry(cursor,&birthday_list, list){
      printk("OS Module : %s .%d.%d.%d",__func__, cursor->day, cursor->month, cursor->year);
    }
  return 0;
}

void simple_exit(void) {
  /* 모듈을 제거할 때는 생성한 연결 리스트도 하나씩 제거하며 끝내도록 하세요. */
  /* 제거를 하기 전에 리스트가 "비어있을 경우""에 대한 예외처리를 하는게 좋겠죠? */
  if(list_empty(&birthday_list)) {
    printk("List is Empty\n");
    return;
  }

  /* TODO: 이제 본격적으로 연결리스트를 탐색하면서 하나씩 제거하도록 하시면 됩니다. */
  /* 다만, 제거를 하면서 연결리스트를 탐색하면 문제가 생길 것 같은데 어떤 방법으로 해결 가능한지 생각해보세요. */
  struct birthday *birthday_;
  struct list_head *ptr, *next;
  list_for_each_safe(ptr, next, &birthday_list){
    birthday_ = list_entry(ptr, struct birthday, list);
    printk("Removing %d.%d.%d",birthday_->day, birthday_->month, birthday_->year);

    list_del(ptr);
    kfree(ptr);
  }
  printk("Removing Module: BDLIST....\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("My name");
