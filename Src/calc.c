#include "calc.h"
#include "OLED.h"
#include "matrix_key.h"

void set_calc_finished_flag() {
  calc_finished_flag = 1;
}

void reset_calc_finished_flag() {
  calc_finished_flag = 0;
}

uint8_t get_calc_finished_flag()
{
  return calc_finished_flag;
}

void calc_Typedef_Init(calc_Typedef *calc)
{
  calc->list_tail = 0;
  calc->stack_tail = 0;
}

uint8_t isStackEmpty(calc_Typedef *calc)
{
  return calc->stack_tail == 0;
}

uint8_t isStackFull(calc_Typedef *calc)
{
  return calc->stack_tail == 256;
}

void stack_push(calc_Typedef *calc, int32_t data_integer, DATA_TYPE type)
{
  if (!isStackFull(calc)) {
    uint8_t count = (calc->stack_tail);
    calc->mem_stack[count].data_integer = data_integer;
    calc->mem_stack[count].type = type;
    (calc->stack_tail)++;
  }
}

data_datatype_Typedef stack_pop(calc_Typedef *calc)
{
  if(!isStackEmpty(calc)) {
    uint8_t count = --(calc->stack_tail);
    return calc->mem_stack[count];
  } else
  {
    data_datatype_Typedef fault_data;
    fault_data.data_integer = 1;
    fault_data.type = OP;
    return fault_data;
  }
}

void num_stack_push_integer(calc_Typedef *calc, int data_integer)
{
  if (!isStackFull(calc)) {
    uint8_t count = (calc->stack_tail);
    calc->mem_stack[count].data_integer = data_integer;
    calc->mem_stack[count].type = NUM;
    (calc->stack_tail)++;
  }
}

void num_stack_push_double(calc_Typedef *calc, double data_double)
{
  if (!isStackFull(calc)) {
    uint8_t count = (calc->stack_tail);
    calc->mem_stack[count].data_double = data_double;
    calc->mem_stack[count].type = FLOAT;
    (calc->stack_tail)++;
  }
}

data_datatype_Typedef num_stack_pop(calc_Typedef *calc)
{
  if(!isStackEmpty(calc)) {
    uint8_t count = --(calc->stack_tail);
    return calc->mem_stack[count];
  } else
  {
    data_datatype_Typedef fault_data;
    fault_data.data_integer = 1;
    fault_data.type = OP;
    return fault_data;
  }
}

uint8_t isListEmpty(calc_Typedef *calc)
{
  return calc->list_tail == 0;
}

uint8_t isListFull(calc_Typedef *calc)
{
  return calc->list_tail == 256;
}

void list_add_integer(calc_Typedef *calc, int32_t data_integer, DATA_TYPE type)
{
  if (!isListFull(calc)) {
    uint8_t count = (calc->list_tail);
    calc->mem_list[count].data_integer = data_integer;
    calc->mem_list[count].type = type;
    calc->list_tail++;
  }
}

void list_add_double(calc_Typedef *calc, double data_double)
{
  if (!isListFull(calc)) {
    uint8_t count = (calc->list_tail);
    calc->mem_list[count].data_double = data_double;
    calc->mem_list[count].type = FLOAT;
    calc->list_tail++;
  }
}

void list_del(calc_Typedef *calc)
{
  if (calc->list_tail != 0) {
    calc->list_tail--;
  }
}

uint32_t isOperator(char *p_c)
{
  switch (*p_c) {
  case '+':
    return OP_PLUS;
    break;

  case '-':
    return OP_MINUS;
    break;

  case '*':
    return OP_TIMES;
    break;

  case '/':
    return OP_DIVIDE;
    break;

  case '(':
    return OP_LEFT;
    break;

  case ')':
    return OP_RIGHT;
    break;

  default:
    return OP_NOT_A_OP;
    break;
  }
}

uint32_t isNum(char *p_c)
{
  if (*p_c>='0'&&*p_c<='9') {
    return 1;
  } else if (*p_c == '.') {
    return 2;
  } else {
    return 0;
  }
}

/*
从左到右扫描中缀表达式，若是操作数，直接存入 post 栈；

若是运算符：
（1）该运算符是左括号 ( , 则直接存入 stack 栈。
（2）该运算符是右括号 )，则将 stack 栈中 ( 前的所有运算符出栈，存入 post 栈。
（3）若该运算符为非括号，则将该运算符和 stack 栈顶运算符作比较：若高于栈顶运算符，则直接存入 stack 栈，
    否则将栈顶运算符出栈（从栈中弹出元素直到遇到发现更低优先级的元素(或者栈为空)为止），存入 post 栈。
（4）当扫描完后，stack 栈中还有运算符时，则将所有运算符出栈，存入 post 栈。
*/

void calc(char *string)
{
  calc_Typedef cm;
  calc_Typedef_Init(&cm);
  int32_t op_type_buffer;
  data_datatype_Typedef temp_data;
  char *p_string = string;

  uint8_t pre_isFloat_flag = 0, isFloat_flag = 0;
  char num_buffer[256];
  int32_t data_integer = 0;
  double data_double = 0;
  uint8_t num_buffer_offset = 0;

  while (*p_string != '\0') {
    if(op_type_buffer = isOperator(p_string)) {
      // 如果是运算符
      if(op_type_buffer == OP_LEFT) {
        // 如果是左括号，直接入栈
        stack_push(&cm, op_type_buffer, OP);
      } else if(op_type_buffer == OP_RIGHT) {
        // 如果是右括号
        do {
          // 不断从stack弹出存入list直到遇到左括号，并删除左括号
          temp_data = stack_pop(&cm);
          list_add_integer(&cm, temp_data.data_integer, temp_data.type);
        } while (!(temp_data.data_integer == OP_LEFT && temp_data.type == OP));
        // 删除左括号
        list_del(&cm);
      } else {
        // 如果是普通运算符
        while(!isStackEmpty(&cm) && (op_type_buffer <= cm.mem_stack[cm.stack_tail-1].data_integer)) {
          // 栈非空且当前运算符优先级不高于栈顶，不断弹出，直到当前运算符优先级高于栈顶或者遇到左括号
          temp_data = stack_pop(&cm);
          list_add_integer(&cm, temp_data.data_integer, temp_data.type);
        }
      // 再将当前运算符压入栈中
      stack_push(&cm, op_type_buffer, OP);
      }
    } else {
      // 如果是数字或者小数点，将当前数字存储到数字缓存数组的偏移量所对应的地方
      num_buffer[num_buffer_offset] = *p_string;
      // 如果是小数点，则将isFloat_flag置1
      if(*p_string == '.') {
        pre_isFloat_flag = 1;
      }
      //偏移量自增
      num_buffer_offset++;
      // 如果下一个不是数字（小数点）或者是字符串末尾
      if(!((*(p_string+1)>='0'&&*(p_string+1)<='9')||*(p_string+1)=='.') || *(p_string+1) == '\0') {
        if (pre_isFloat_flag) {
          isFloat_flag = 1;
          pre_isFloat_flag = 0;
        }
        // 数字缓存数组的偏移量所对应的地方设为'\0'
        num_buffer[num_buffer_offset] = '\0';
        // 如果数字是浮点数
        if(isFloat_flag) {
          data_double = atof(num_buffer);
          list_add_double(&cm, data_double);
        } else {    // 如果是整型数
          data_integer = atoi(num_buffer);
          list_add_integer(&cm, data_integer, NUM);
        }
        // 重置偏移量和flag
        isFloat_flag = 0;
        num_buffer_offset = 0;
      }
    }
    p_string++;
  }
  while (!isStackEmpty(&cm)) {
    // 将栈中的运算符依次弹出并加入到队列
    temp_data = stack_pop(&cm);
    list_add_integer(&cm, temp_data.data_integer, temp_data.type);
  }
  // 在列表依次扫描
  // 如果是数字，直接入栈
  // 如果是运算符，弹出两个数字，进行运算
  uint8_t list_offset = 0;
  calc_Typedef cc;
  calc_Typedef_Init(&cc);
  double temp_result_double ;
  uint8_t cc_stack_tail;

#define GET_NUM(x) cc.mem_stack[cc_stack_tail - x].type == NUM ? cc.mem_stack[cc_stack_tail - x].data_integer : cc.mem_stack[cc_stack_tail - x].data_double
#define OP_CALC(OP)                                \
  temp_result_double = (GET_NUM(2))OP(GET_NUM(1)); \
  num_stack_pop(&cc);                              \
  num_stack_pop(&cc);                              \
  num_stack_push_double(&cc, temp_result_double);

  for (; list_offset < cm.list_tail; list_offset++) {
    switch (cm.mem_list[list_offset].type)
    {
    case NUM:
      num_stack_push_integer(&cc, cm.mem_list[list_offset].data_integer);
      break;

    case FLOAT:
      num_stack_push_double(&cc, cm.mem_list[list_offset].data_double);
      break;

    case OP:
      cc_stack_tail = cc.stack_tail;
      // if(cc.mem_stack[cc_stack_tail - 1].type == NUM && cc.mem_stack[cc_stack_tail - 2].type == NUM)
      switch (cm.mem_list[list_offset].data_integer)
      {
      case OP_PLUS:
        OP_CALC(+);
        break;

      case OP_MINUS:
        OP_CALC(-);
        break;

      case OP_TIMES:
        OP_CALC(*);
        break;

      case OP_DIVIDE:
        OP_CALC(/);
        break;
      
      default:
        break;
      }
      break;
    
    default:
      break;
    }
  }
  int32_t temp = temp_result_double * 1000000;
  int32_t ld1 = temp/1000000, ld2 = temp%1000000;
  clearScreen();
  setCharCursor(0, 0);
  sprintf(getStr(), "%f", temp_result_double);
  set_calc_finished_flag();
  set_clearScreen_flag();
  return;
}