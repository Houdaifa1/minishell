<div align="center">

# 🐚 minishell

**Build your own shell. Pipes, redirections, signals, builtins — the full Unix experience.**

![C](https://img.shields.io/badge/language-C-blue?style=for-the-badge&logo=c)
![42](https://img.shields.io/badge/school-42-black?style=for-the-badge)
![Score](https://img.shields.io/badge/score-100%2F100-brightgreen?style=for-the-badge)

</div>

---

## 🧠 What is minishell?

`minishell` is one of the most complex projects at 42. You implement a fully functional **Unix shell** in C — a simplified but real bash-like interpreter that handles command execution, piping, redirections, environment variables, signal handling, and built-in commands.

It's a deep dive into how shells actually work under the hood.

---

## ✅ Features

### Command Execution
- Execute binaries via `PATH` resolution (`/usr/bin/ls`, `echo`, etc.)
- Handle single commands, pipelines (`|`), and command sequences

### Redirections
| Syntax | Behavior |
|--------|---------|
| `< file` | Redirect stdin from file |
| `> file` | Redirect stdout to file (truncate) |
| `>> file` | Redirect stdout to file (append) |
| `<< DELIM` | Here-document (heredoc) |

### Pipes
```bash
ls -la | grep ".c" | wc -l
```

### Environment Variables
- `$VAR` expansion
- `$?` — exit status of last command
- Full environment inheritance

### Quoting
- `'single quotes'` — no expansion
- `"double quotes"` — variable expansion inside

### Built-in Commands
| Command | Behavior |
|---------|---------|
| `echo [-n]` | Print text |
| `cd [path]` | Change directory |
| `pwd` | Print working directory |
| `export [VAR=val]` | Set environment variable |
| `unset VAR` | Remove env variable |
| `env` | Print all environment variables |
| `exit [code]` | Exit the shell |

### Signals
| Signal | Behavior |
|--------|---------|
| `Ctrl+C` | `SIGINT` — new prompt |
| `Ctrl+D` | EOF — exit shell |
| `Ctrl+\` | `SIGQUIT` — ignored in interactive mode |

---

## 🚀 Usage

```bash
git clone https://github.com/Houdaifa1/minishell
cd minishell
make
./minishell
```

```
minishell$ echo "Hello, $USER!"
Hello, Houdaifa!
minishell$ ls | grep .c | wc -l
42
minishell$ cat << EOF
> This is
> a heredoc
> EOF
minishell$ exit
```

---

## 🔧 Build

```bash
make        # Compile
make clean  # Remove objects
make fclean # Full cleanup
make re     # Rebuild
```

---

## 📁 Architecture

```
minishell/
├── src/
│   ├── lexer/        # Tokenization
│   ├── parser/       # AST construction
│   ├── executor/     # Command execution, pipes, redirections
│   ├── builtins/     # Built-in command implementations
│   ├── signals/      # Signal handling
│   └── env/          # Environment management
├── includes/
└── Makefile
```

---

<div align="center">
<i>You don't truly understand bash until you've written your own.</i>
</div>
