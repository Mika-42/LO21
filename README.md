# LO21

## Compilation avec `make`
*Ce makefile a été conçu pour être exécuté dans un environnement linux*

+ Compiler le programme pour le déboguage
```bash
make build-debug
```

+ Compiler le programme pour la production
```bash
make build-release
```

+ Compiler les tests unitaires
```bash
    make build-unit-test
```

+ Déboguer le programme
```bash
make run-debug
```

+ Exécuter le programme
```bash
make run
```

+ Exécuter un test unitaire
```bash
make run-unit-test FILENAME=<nom du fichier>
```

+ Exécuter l'intégralité des test unitaires
```bash
make run-all-unit-test
```

+ Déboguer un test unitaire
```bash
make run-unit-test-debug FILENAME=<nom du fichier>
```

+ Effacer le répertoire de compilation
```bash
make clean
```
+ Effacer le répertoire des test unitaires
```bash
make clean-unit-test
```

+ Compiler puis exécuter le programme
```bash
make build run
```

