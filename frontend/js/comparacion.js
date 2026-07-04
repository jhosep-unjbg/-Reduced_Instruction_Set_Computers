function inicializarComparacion() {
  cargarModuloComparacion();

  document
    .getElementById("btnAnalizarComparacion")
    ?.addEventListener("click", cargarModuloComparacion);
}

async function cargarModuloComparacion() {
  const datosBackend = await getData("/comparacion/risc-cisc");

  if (datosBackend) {
    pintarComparacion(datosBackend);
    return;
  }

  const risc = JSON.parse(localStorage.getItem("resultadoRisc"));
  const cisc = JSON.parse(localStorage.getItem("resultadoCisc"));

  if (!risc || !cisc) {
    mostrarComparacionVacia();
    return;
  }

  pintarComparacion({ risc, cisc });
}

function pintarComparacion(datos) {
  const risc = datos.risc;
  const cisc = datos.cisc;

  document.getElementById("cmpInstr").textContent =
    `${risc.instrucciones} vs ${cisc.instrucciones}`;

  document.getElementById("cmpMem").textContent =
    `${risc.memoria} vs ${cisc.memoria}`;

  document.getElementById("cmpPipe").textContent =
    risc.pipeline >= cisc.pipeline ? "RISC" : "CISC";

  document.getElementById("cmpCodigo").textContent =
    risc.instrucciones < cisc.instrucciones ? "RISC" : "CISC";

  document.getElementById("txtRiscInstr").textContent = risc.instrucciones;
  document.getElementById("txtCiscInstr").textContent = cisc.instrucciones;

  document.getElementById("txtRiscMem").textContent = risc.memoria;
  document.getElementById("txtCiscMem").textContent = cisc.memoria;

  const maxInstr = Math.max(risc.instrucciones, cisc.instrucciones);
  const maxMem = Math.max(risc.memoria, cisc.memoria);

  document.getElementById("barRiscInstr").style.width =
    `${(risc.instrucciones / maxInstr) * 100}%`;

  document.getElementById("barCiscInstr").style.width =
    `${(cisc.instrucciones / maxInstr) * 100}%`;

  document.getElementById("barRiscMem").style.width =
    `${(risc.memoria / maxMem) * 100}%`;

  document.getElementById("barCiscMem").style.width =
    `${(cisc.memoria / maxMem) * 100}%`;

  document.getElementById("barRiscComp").style.width = `${risc.complejidad}%`;
  document.getElementById("barCiscComp").style.width = `${cisc.complejidad}%`;

  document.getElementById("barRiscPipe").style.width = `${risc.pipeline}%`;
  document.getElementById("barCiscPipe").style.width = `${cisc.pipeline}%`;

  generarConclusionComparacion(risc, cisc);
}

function generarConclusionComparacion(risc, cisc) {
  const mismoResultado = risc.resultado === cisc.resultado;

  document.getElementById("conclusionComparacion").textContent =
    mismoResultado
      ? "Ambas arquitecturas producen el mismo resultado."
      : "Las arquitecturas producen resultados diferentes.";

  const reduccion = (
    ((risc.instrucciones - cisc.instrucciones) / risc.instrucciones) * 100
  ).toFixed(1);

  document.getElementById("resultadoComparacion").textContent =
    `CISC reduce el código en ${reduccion}%, mientras RISC favorece mejor el pipeline. Resultado: ${risc.resultado}`;
}

function mostrarComparacionVacia() {
  document.getElementById("conclusionComparacion").textContent =
    "Primero ejecuta los módulos RISC y CISC.";

  document.getElementById("resultadoComparacion").textContent =
    "No hay datos suficientes para comparar.";
}