console.log("Frontend principal cargado.");

document.addEventListener("DOMContentLoaded", () => {
  if (document.body.dataset.page === "pipeline") {
    inicializarPipeline();
  }

  if (document.body.dataset.page === "monociclo") {
    inicializarMonociclo();
  }

  if (document.body.dataset.page === "risc") {
    inicializarRisc();
  }

  if (document.body.dataset.page === "cisc") {
    inicializarCisc();
  }

  if (document.body.dataset.page === "comparacion") {
    inicializarComparacion();
  }
  if (document.body.dataset.page === "comparacion-pipeline") {
  inicializarComparacionPipeline();
}
});