#include "safe_trace.h"

bool is_valid_and_safe_string(const char *s) {
    if (s == NULL) {
        return false;
    }

    while (*s != '\0') {
        switch (*s) {
            case '"':
            case '\\':
                return false;
            default:
                break;
        }
        s++;
    }
    return true;
}

const char *get_prefix(ETypeTrace_t type) {
    switch (type) {
        case DEBUG: return "[DEBUG]";
        case INFO: return "[INFO]";
        case WARNING: return "[WARNING]";
        case ERROR: return "[ERROR]";
        default: return "";
    }
}

void safe_trace_implementation(ETypeTrace_t trace_type, const char *args[])
{

    const char *prefix = NULL;
    
        // Verificar la validez y seguridad de los argumentos
    bool args_valid = true;
    for (int i = 0; args[i] != NULL; ++i) {
        if (!is_valid_and_safe_string(args[i])) {
            args_valid = false;
            break;
        }
    }
    prefix = get_prefix(trace_type);
    // Llamar a safe_trace_implementation solo si los argumentos son válidos y seguros
    if (args_valid) {
        fputs(prefix, stdout);
        fputs(": [ ", stdout);

        for (int i = 0; args[i] != NULL; ++i) {
            fputs(args[i], stdout);
            putchar(' ');  // Agregar espacio entre los elementos
        }

        puts("]");
    } else {
        puts("[TRACE ERROR][INVALID ARGUMENT]");
    }

}

