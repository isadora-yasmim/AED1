#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArvoreAVL.h"

/* 
Nomes dos alunos:
1. Ana Luísa Pereira dos Santos
2. Isadora Yasmim da Silva
3. Verônica Ribeiro Oliveira Palmeira
*/

// Array de palavras para carregar no dicionario
char *dados[] = {
  "Beep", "CloseHandle", "CreateFile", "GetConsoleScreenBufferInfo", "GetLastError", "GetModuleHandle",
		"GetProcAddress", "MessageBox", "SetConsoleCursorPosition", "SetConsoleTextAttribute",
		"Sleep", "WriteFile", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
		"_Noreturn", "_Static_assert", "_Thread_local", "__builtin_clz", "__builtin_ctz", "__builtin_popcount",
		"__sync_fetch_and_add", "_exit", "abort", "abs", "accept", "access", "acos", "acosf", "acosl", "alarm",
		"alloca", "asctime", "asin", "asinf", "asinl", "assert", "at_quick_exit", "atan", "atan2", "atan2f",
		"atan2l", "atanf", "atanl", "atexit", "atof", "atoi", "atol", "atoll", "auto", "break", "bsearch", "btowc",
		"c16rtomb", "c32rtomb", "cabs", "cabsf", "cabsl", "cacos", "cacosf", "cacosl", "calloc", "carg", "cargf",
		"cargl", "case", "casin", "casinf", "casinl", "catan", "catanf", "catanl", "cbrt", "cbrtf", "cbrtl", "ccos",
		"ccosf", "ccosl", "ceil", "ceilf", "ceill", "char", "chdir", "chmod", "chown", "cimag", "cimagf", "cimagl",
		"clearerr", "clock", "clog", "clogf", "clogl", "close", "closedir", "clrscr", "cnd_broadcast", "cnd_destroy",
		"cnd_init", "cnd_signal", "cnd_timedwait", "cnd_wait", "const", "continue", "copysign", "copysignf",
		"copysignl", "cos", "cosf", "cosl", "cpow", "cpowf", "cpowl", "cprintf", "cproj", "cprojf", "cprojl", "cputs",
		"creal", "crealf", "creall", "cscanf", "csin", "csinf", "csinl", "csqrt", "csqrtf", "csqrtl", "ctan", "ctanf",
		"ctanl", "ctime", "default", "delline", "difftime", "div", "do", "double", "dup", "dup2", "else", "enum",
		"erf", "erfc", "erfcf", "erfcl", "erff", "erfl", "execl", "execle", "execlp", "execv", "execve", "execvp",
		"exit", "exp", "exp2", "exp2f", "exp2l", "expf", "expl", "expm1", "expm1f", "expm1l", "extern", "fabs", "fabsf",
		"fabsl", "fclose", "fcntl", "fdim", "fdimf", "fdiml", "feclearexcept", "fegetenv", "fegetexceptflag",
		"fegetround", "feholdexcept", "feof", "feraiseexcept", "ferror", "fesetenv", "fesetexceptflag",
		"fesetround", "fetestexcept", "feupdateenv", "fflush", "fgetc", "fgetpos", "fgets", "fgetwc",
		"fgetws", "float", "floor", "floorf", "floorl", "fma", "fmaf", "fmal", "fmax", "fmaxf", "fmaxl", "fmin", "fminf",
		"fminl", "fmod", "fmodf", "fmodl", "fopen", "for", "fork", "fpathconf", "fprintf", "fputc", "fputs", "fputwc",
		"fputws", "fread", "free", "freopen", "frexp", "frexpf", "frexpl", "fscanf", "fseek", "fsetpos", "fstat",
		"ftell", "fwide", "fwprintf", "fwscanf", "getc", "getch", "getchar", "getche", "getcwd", "getegid",
		"getenv", "geteuid", "getgid", "getpid", "getppid", "gets", "gettext", "getuid", "getwc", "getwchar",
		"gmtime", "goto", "gotoxy", "hypot", "hypotf", "hypotl", "if", "ilogb", "ilogbf", "ilogbl", "imaxabs",
		"imaxdiv", "inline", "insline", "int", "ioctl", "isalnum", "isalpha", "isblank", "iscntrl", "isdigit",
		"isgraph", "islower", "isprint", "ispunct", "isspace", "isupper", "iswalnum", "iswalpha", "iswblank",
		"iswcntrl", "iswdigit", "iswgraph", "iswlower", "iswprint", "iswpunct", "iswspace", "iswupper",
		"iswxdigit", "isxdigit", "itoa", "kbhit", "kill", "labs", "ldexp", "ldexpf", "ldexpl", "ldiv", "lgamma",
		"lgammaf", "lgammal", "link", "llabs", "lldiv", "llrint", "llrintf", "llrintl", "llround", "llroundf",
		"llroundl", "localeconv", "localtime", "log", "log10", "log10f", "log10l", "log1p", "log1pf", "log1pl",
		"log2", "log2f", "log2l", "logb", "logbf", "logbl", "long", "longjmp", "lrint", "lrintf", "lrintl", "lround",
		"lroundf", "lroundl", "lseek", "ltoa", "malloc", "mbrlen", "mbrtoc16", "mbrtoc32", "mbrtowc", "mbstowcs",
		"mbtowc", "memchr", "memcmp", "memcpy", "memmove", "memset", "mkdir", "mkfifo", "mktime", "modf", "modff",
		"modfl", "mtx_destroy", "mtx_init", "mtx_lock", "mtx_timedlock", "mtx_trylock", "mtx_unlock",
		"nan", "nanf", "nanl", "nearbyint", "nearbyintf", "nearbyintl", "nextafter", "nextafterf", "nextafterl",
		"nexttoward", "nexttowardf", "nexttowardl", "open", "opendir", "pathconf", "perror", "pipe", "pow",
		"powf", "powl", "printf", "putc", "putch", "putchar", "puts", "puttext", "putwc", "putwchar", "qsort",
		"quick_exit", "raise", "rand", "read", "readdir", "realloc", "register", "remainder", "remainderf",
		"remainderl", "remove", "remquo", "remquof", "remquol", "rename", "restrict", "return", "rewind",
		"rewinddir", "rint", "rintf", "rintl", "rmdir", "round", "roundf", "roundl", "scalbln", "scalblnf",
		"scalblnl", "scalbn", "scalbnf", "scalbnl", "scanf", "select", "setbuf", "setgid", "setjmp", "setlocale",
		"setpgid", "setsid", "setuid", "setvbuf", "short", "sigaction", "sigaddset", "sigdelset", "sigemptyset",
		"sigfillset", "sigismember", "signal", "signed", "sigpending", "sigprocmask", "sigsuspend",
		"sin", "sinf", "sinh", "sinhf", "sinhl", "sinl", "sizeof", "sleep", "snprintf", "sprintf", "sqrt", "sqrtf",
		"sqrtl", "srand", "sscanf", "stat", "static", "strcat", "strchr", "strcmp", "strcoll", "strcpy", "strcspn",
		"strdup", "strerror", "strftime", "stricmp", "strlen", "strlwr", "strncat", "strncmp", "strncpy",
		"strnicmp", "strpbrk", "strrchr", "strspn", "strstr", "strtod", "strtof", "strtoimax", "strtok",
		"strtol", "strtold", "strtoll", "strtoul", "strtoull", "strtoumax", "struct", "strupr", "strxfrm",
		"switch", "swprintf", "swscanf", "symlink", "system", "tan", "tanf", "tanh", "tanhf", "tanhl", "tanl",
		"tcgetpgrp", "tcsetpgrp", "textbackground", "textcolor", "tgamma", "tgammaf", "tgammal", "thrd_create",
		"thrd_current", "thrd_detach", "thrd_equal", "thrd_exit", "thrd_join", "thrd_sleep", "thrd_yield",
		"time", "tmpfile", "tmpnam", "tolower", "toupper", "towctrans", "towlower", "towupper", "trunc",
		"truncf", "truncl", "tss_create", "tss_delete", "tss_get", "tss_set", "typedef", "ultoa", "uname",
		"ungetc", "ungetch", "ungetwc", "union", "unlink", "unsigned", "va_arg", "va_copy", "va_end", "va_start",
		"vfprintf", "vfscanf", "vfwprintf", "vfwscanf", "void", "volatile", "vprintf", "vscanf", "vsnprintf",
		"vsprintf", "vsscanf", "vswprintf", "vswscanf", "vwprintf", "vwscanf", "wait", "waitpid", "wcrtomb",
		"wcscat", "wcschr", "wcscmp", "wcscoll", "wcscpy", "wcscspn", "wcsftime", "wcslen", "wcsncat", "wcsncmp",
		"wcsncpy", "wcspbrk", "wcsrchr", "wcsrtombs", "wcsspn", "wcsstr", "wcstod", "wcstof", "wcstok", "wcstol",
		"wcstold", "wcstoll", "wcstombs", "wcstoul", "wcstoull", "wctob", "wctrans", "wctype", "wherex",
		"wherey", "while", "window", "wmemchr", "wmemcmp", "wmemcpy", "wmemmove", "wmemset", "wprintf", "write",
		"wscanf"

};

// Função para inserir uma nova palavra no dicionário
void inserirPalavra(ArvAVL* raiz) {
    char palavra[256];
    printf("Digite a palavra a ser inserida: ");
    
    if(fgets(palavra, sizeof(palavra), stdin) == NULL) {
        fprintf(stderr, "Erro na leitura da entrada.\n");
        return;
    }
    
    // Remove o \n no final
    palavra[strcspn(palavra, "\n")] = '\0';
    
    // Verifica se é string vazia ou só espaços
    if(ehStringVazia(palavra)) {
        printf("Erro: Digite uma palavra válida (não vazia ou apenas espaços)\n");
        return;
    }
    
    if(insere_ArvAVL(raiz, palavra)) {
        printf("Palavra '%s' inserida com sucesso!\n", palavra);
    } else {
        printf("Palavra '%s' já existe no dicionário ou houve um erro na inserção.\n", palavra);
    }
}

// Funcao principal para testar a arvore AVL
int main() {
    // Cria uma arvore AVL vazia
    ArvAVL* raiz = cria_ArvAVL();
    if(raiz == NULL) {
        fprintf(stderr, "Falha critica: Nao foi possivel inicializar o dicionario.\n");
        return EXIT_FAILURE;
    }

    // Carrega o vocabulario na arvore
    int n = sizeof(dados)/sizeof(dados[0]);
    carregaVocabulario(raiz, dados, n);

    printf("=== Dicionario com Autocompletar ===\n");
    
    char linha[256];
    while(1) {
        printf("\nOpcoes:\n");
        printf("1. Inserir palavra\n");
        printf("2. Buscar por prefixo\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        
        if(fgets(linha, sizeof(linha), stdin) == NULL) {
            if(feof(stdin)) break;
            fprintf(stderr, "Erro na leitura da entrada.\n");
            continue;
        }
        
        // Remove o \n no final
        linha[strcspn(linha, "\n")] = '\0';
        
        // Verifica se é string vazia ou só espaços
        if(ehStringVazia(linha)) {
            printf("Erro: Digite uma opcao valida\n");
            continue;
        }
        
        if(strcmp(linha, "1") == 0) {
            inserirPalavra(raiz);
        } 
        else if(strcmp(linha, "2") == 0) {
            printf("Digite o prefixo para buscar: ");
            if(fgets(linha, sizeof(linha), stdin) == NULL) {
                if(feof(stdin)) break;
                fprintf(stderr, "Erro na leitura da entrada.\n");
                continue;
            }
            
            linha[strcspn(linha, "\n")] = '\0';
            
            if(ehStringVazia(linha)) {
                printf("Erro: Digite um prefixo valido (nao vazio ou apenas espacos)\n");
                continue;
            }
            
            if(strcmp(linha, "sair") == 0) break;
            
            autocomplete(raiz, linha);
        }
        else if(strcmp(linha, "3") == 0 || strcmp(linha, "sair") == 0) {
            break;
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    
    // Libera a memoria da arvore
    libera_ArvAVL(raiz);
    printf("Programa encerrado com sucesso.\n");
    return EXIT_SUCCESS;
}
