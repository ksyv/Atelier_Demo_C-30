const filDeCommentaires = [
  {
    id: 1,
    auteur: "Alice",
    texte: "Super article !",
    reponses: [
      {
        id: 2,
        auteur: "Bob",
        texte: "Je suis d'accord, très clair.",
        reponses: []
      },
      {
        id: 3,
        auteur: "Charlie",
        texte: "Merci pour le partage !",
        reponses: [
          {
            id: 4,
            auteur: "Alice",
            texte: "De rien Charlie.",
            reponses: []
          }
        ]
      }
    ]
  },
  {
    id: 5,
    auteur: "David",
    texte: "Je n'ai pas tout compris sur la fin...",
    reponses: []
  }
];

function compterCommentaires(commentaires) {
    let total = 0;

    commentaires.forEach(commentaire => {
        total += 1;
        if (commentaire.reponses && commentaire.reponses.length > 0) {
            total += compterCommentaires(commentaire.reponses);
        }
    })

    return total;
}

console.log(`Il y a ${compterCommentaires(filDeCommentaires)} commentaires au total.`);