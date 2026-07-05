console.log("Frontend principal cargado.");

document.addEventListener("DOMContentLoaded", async () => {
  const page = document.body.dataset.page;

  if (page === "dashboard" || page === "index") {
    await cargarHistorialDashboard();
  }

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

async function cargarHistorialDashboard() {
  const tabla = document.getElementById("tablaHistorialDashboard");

  if (!tabla) return;

  tabla.innerHTML = `
    <tr>
      <td colspan="5">Cargando historial...</td>
    </tr>
  `;

  const datos = await getData("/api/historial");

  if (!datos || !Array.isArray(datos.historial) || datos.historial.length === 0) {
    tabla.innerHTML = `
      <tr>
        <td colspan="5">No hay simulaciones registradas.</td>
      </tr>
    `;
    return;
  }

  tabla.innerHTML = "";

  datos.historial
    .slice()
    .reverse()
    .forEach((item) => {
      tabla.innerHTML += `
        <tr>
          <td>${item.id || "-"}</td>
          <td>${item.fecha || "-"}</td>
          <td>${item.modulo || "-"}</td>
          <td>${item.parametros || "-"}</td>
          <td>${item.resultado || "-"}</td>
        </tr>
      `;
    });
}