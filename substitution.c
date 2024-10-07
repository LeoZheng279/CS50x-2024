// Problem Set 2 - Substitution
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
// 声明两个要用到的函数
int f_verify(string pass);
string encrypt(string plain, string pass);
// 主进程
int main(int argc, string argv[])
{ // 如果不传入参数，那么提示使用方法
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // 初始化密码变量pass
    int counter, total;
    string pass = argv[1];
    total = strlen(pass);

    // 将pass变量统一转化为大写形式
    for (int i = 0; i < total; i++)
        pass[i] = toupper(pass[i]);

    // 验证密码是否有效且不重不漏
    if (f_verify(pass))
        return 1;
    // 提示用户输入明文并进行加密，输出结果
    string plain = get_string("plaintext:  ");
    string cipher = encrypt(plain, pass);
    printf("ciphertext: %s\n", cipher);
}
// 验证思路：
// 创建一个26个数组成的数组，代表26个字母，每个字母在密码中出现时，就把那个字母对应的数组位置记为1，
// 最后再检查，若数组中有非1元素，则证明有重复或者有缺漏
int f_verify(string pass)
{
    int verify[26];
    for (int i = 0; i < 26; i++)
    {
        if (pass[i] >= 'A' && pass[i] <= 'Z')
        {
            verify[pass[i] - 65] = 1;
        }
        else if (pass[i] < 'A' || pass[i] > 'Z')
        {
            printf("Key must be one of 26 characters.\n");
            return 1;
        }
    }
    // 验证26个字母不重不漏
    for (int j = 0; j < 26; j++)
    {
        if (verify[j] != 1)
        {
            printf("Key must contain 26 characters without duplication.\n");
            return 1;
        }
    }
    return 0;
}

// 加密函数。思路：利用C语言的ASCII对应性
string encrypt(string plain, string pass)
{
    int plain_l = strlen(plain);
    string cipher = plain;
    for (int i = 0; i < plain_l; i++)
    {
        if (plain[i] >= 'A' && plain[i] <= 'Z')
            cipher[i] = pass[plain[i] - 65];
        else if (plain[i] >= 'a' && plain[i] <= 'z')
            cipher[i] = tolower(pass[plain[i] - 'a' + 'A' - 65]);
        else
            cipher[i] = plain[i];
    }
    return cipher;
}
