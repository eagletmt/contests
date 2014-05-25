#include <stdio.h>

typedef struct expr_tag
{
  char v;
  struct expr_tag *lhs, *rhs;
} expr;

static expr store[300];
expr *freelist;

expr *var(char c)
{
  expr *e = freelist++;
  e->v = c;
  e->lhs = e->rhs = NULL;
  return e;
}

expr *binop(char op, expr *l, expr *r)
{
  expr *e = freelist++;
  e->v = op;
  e->lhs = l;
  e->rhs = r;
  return e;
}

void ppr(expr *e, int level)
{
  if (!e->lhs) {
    putchar(e->v);
  } else {
    int llv, rlv;
    switch (e->v) {
      case '*':
        llv = rlv = 4;  break;
      case '/':
        llv = 4;  rlv = 5;  break;
      case '+':
        llv = rlv = 1;  break;
      case '-':
        llv = 1;  rlv = 2;  break;
    }

    if (level > llv) {
      putchar('(');
    }
    ppr(e->lhs, llv);
    putchar(e->v);
    ppr(e->rhs, rlv);
    if (level > llv) {
      putchar(')');
    }
  }
}

expr *parse_expr();
expr *parse_factor()
{
  const char c = getchar();
  if (c == '(') {
    expr *e = parse_expr();
    (void)getchar();
    return e;
  } else {
    expr *e = var(c);
    return e;
  }
}

expr *parse_term()
{
  expr *l = parse_factor();
  char c = getchar();
  while (c != '\n' && (c == '*' || c == '/')) {
    expr *r = parse_factor();
    l = binop(c, l, r);
    c = getchar();
  }
  ungetc(c, stdin);
  return l;
}

expr *parse_expr()
{
  expr *l = parse_term();
  char c = getchar();
  while (c != '\n' && (c == '+' || c == '-')) {
    expr *r = parse_term();
    l = binop(c, l, r);
    c = getchar();
  }
  ungetc(c, stdin);
  return l;
}

int main()
{
  int N;
  scanf("%d", &N);
  (void)getchar();
  while (N-- > 0) {
    freelist = store;
    expr *e = parse_expr();
    ppr(e, 0);
    (void)getchar();
    putchar('\n');
  }
  return 0;
}
