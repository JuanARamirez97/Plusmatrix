#/usr/bin/env bash

_plusmatrix_completions() {
    # Local variables that bash uses to know where the cursor is
    local cur prev opts colors
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"     # La palabra actual que estás escribiendo
    prev="${COMP_WORDS[COMP_CWORD-1]}"  # La palabra anterior

    # Principal options
    opts="-h --help -c -f"
    
    # Available colors
    colors="green red blue cyan magenta yellow white"

    # Logic
    case "${prev}" in
        # If the previous word was -c, we suggest the colors
        -c)
            COMPREPLY=( $(compgen -W "${colors}" -- "${cur}") )
            return 0
            ;;
        # If it was -f, we don't suggest anything (we expect a number)
        -f)
            COMPREPLY=()
            return 0
            ;;
        # If it's anything else (or the beginning), we suggest flags
        *)
            COMPREPLY=( $(compgen -W "${opts}" -- "${cur}") )
            return 0
            ;;
    esac
}

# We tell Bash to use the function above for the 'plusmatrix' command
complete -F _plusmatrix_completions plusmatrix