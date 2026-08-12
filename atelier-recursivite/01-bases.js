function countdown(n){
    //1. condition d'arrêt
    if (n <= 0){
        console.log("Décollage!!!!");
        return;
    }

    console.log(n);
    //2. l'appel récursif -> rapprocher de la condition d'arrêt
    countdown(n - 1);
}

countdown(3);