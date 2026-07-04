console.log("Frontend del Simulador de Arquitectura cargado correctamente.");

document.addEventListener("DOMContentLoaded", () => {
  const cards = document.querySelectorAll(".card");

  cards.forEach(card => {
    card.addEventListener("click", () => {
      card.classList.add("selected");

      setTimeout(() => {
        card.classList.remove("selected");
      }, 300);
    });
  });
});