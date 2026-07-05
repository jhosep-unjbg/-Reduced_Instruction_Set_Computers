console.log("Frontend principal cargado.");

document.addEventListener("DOMContentLoaded", () => {
  const page = document.body.dataset.page;

  if (page === "pipeline" && typeof inicializarPipeline === "function") {
    inicializarPipeline();
  }

  if (page === "monociclo" && typeof inicializarMonociclo === "function") {
    inicializarMonociclo();
  }

  if (page === "risc" && typeof inicializarRisc === "function") {
    inicializarRisc();
  }

  if (page === "cisc" && typeof inicializarCisc === "function") {
    inicializarCisc();
  }

  if (page === "comparacion" && typeof inicializarComparacion === "function") {
    inicializarComparacion();
  }

  if (
    page === "comparacion-pipeline" &&
    typeof inicializarComparacionPipeline === "function"
  ) {
    inicializarComparacionPipeline();
  }

  if (
    page === "pipeline-avanzado" &&
    typeof initPipelineAvanzado === "function"
  ) {
    initPipelineAvanzado();
  }
});