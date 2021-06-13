# Welcome to 420sh 👋
![Version](https://img.shields.io/badge/version-1-blue.svg?cacheSeconds=2592000)

> A C based shell with voice recognition

## Compiling

```sh
make
``` 

## Run
After compiling, run :

```sh
./main
```

First, Set the environment variable GOOGLE_APPLICATION_CREDENTIALS to the path of the JSON file that contains your service account key

Then, [Install and initialize the Cloud SDK](https://cloud.google.com/sdk/docs/install).

To run a command with voice recognition (in the shell): 

```sh
start-voice
```

If you want command to run on startup (i.e: alias, change-color, neofetch, ...) :

First, create '.config' file, then input a command per line.

You can also add aliases via the following command : 

```sh
alias alias_name cmd
```

## Author

👤 **Marius ANDRE (marius.andre)** *In Charge of the Shell*

* Github: [@bobaiep](https://github.com/bobaiep)

👤 **Adam ELZAIM (adam.elzaim)** *In Charge of the Web*

* Github: [@AdamElzaim](https://github.com/AdamElzaim)

👤 **Nicola BRANKOVIC (nicola.brankovic)** *In Charge of the Voice Recognition* 

* Github: [@Smajser12](https://github.com/Smajser12)


***
_This README was generated with ❤️ by [readme-md-generator](https://github.com/kefranabg/readme-md-generator)_
