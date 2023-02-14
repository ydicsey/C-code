/*
 * @lc app=leetcode.cn id=150 lang=c
 *
 * [150] 逆波兰表达式求值
 */

// @lc code=start

// stack in c
int top = -1;
int stack[10005];

void push(int x)
{
    top++;
    stack[top] = x;
    printf("%d", top);
}

int pop()
{
    if (top == -1)
    {
        printf("\nUnderflow!!");
        return 0;
    }
    return stack[top--];
}

int peek()
{
    return stack[top];
}

int evalRPN(char ** tokens, int tokensSize){
    top = -1;
    if(tokensSize == 1)
    {
        return (int)strtol(tokens[0], NULL, 10);
    }

    for(int i = 0; i < tokensSize; i++)
    {
        char* tmp = tokens[i];
        printf("\n%s  ", tmp);
        // if token[i] is Number
        if(!( !strncmp(tmp, "+", 2) || !strncmp(tmp, "-", 2) || !strncmp(tmp, "*", 2) || !strncmp(tmp, "/", 2)))
        {
            int n = (int)strtol(tokens[i], NULL, 10);
            push(n);
        }
        else
        {
            int b = pop(), a = pop();
            switch (tmp[0])
            {
            case '+':
                push(a+b);
                break;
            case '-':
                push(a-b);
                break;
            case '*':
                push(a*b);
                break;
            case '/':
                push(a/b);
                break;
            default:
                break;
            }
        }
    }
    return peek();
}
// @lc code=end