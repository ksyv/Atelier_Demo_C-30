const dossierRacine = {
  nom: "Projet_Web",
  fichiers: [
    { nom: "index.html", fichiers: [] },
    { 
      nom: "assets", 
      fichiers: [
        { nom: "logo.png", fichiers: [] },
        { 
          nom: "css", 
          fichiers: [
            { nom: "style.css", fichiers: [] }
          ] 
        }
      ] 
    }
  ]
};

function explorerDossier(dossier, niveau = 0) {
    const indentation = "---".repeat(niveau);
    console.log(`${indentation} ${dossier.nom}`);

    dossier.fichiers.forEach(sousDossier => {
        explorerDossier(sousDossier, niveau + 1);
    });
}

explorerDossier(dossierRacine);