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

  pintarCodigoComparacion();

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

  const maxInstr = Math.max(risc.instrucciones, cisc.instrucciones, 1);
  const maxMem = Math.max(risc.memoria, cisc.memoria, 1);

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

  dibujarGraficoXY(risc, cisc);
  generarConclusionComparacion(risc, cisc);
}

function pintarCodigoComparacion() {
  document.getElementById("codigoRiscComparacion").innerHTML = `
    <div>LI R0, 0x100</div>
    <div>LW R1, 0(R0)</div>
    <div>LW R2, 4(R0)</div>
    <div>LW R3, 8(R0)</div>
    <div>LW R4, 12(R0)</div>
    <div>ADD R5, R1, R2</div>
    <div>SUB R6, R3, R4</div>
    <div>MUL R7, R5, R6</div>
    <div>SW R7, 16(R0)</div>
  `;

  document.getElementById("codigoCiscComparacion").innerHTML = `
    <div>MOV AX, [0x100]</div>
    <div>ADD AX, [0x104]</div>
    <div>MOV BX, [0x108]</div>
    <div>SUB BX, [0x10C]</div>
    <div>MUL BX</div>
    <div>MOV [0x110], AX</div>
  `;
}

function dibujarGraficoXY(risc, cisc) {
  const canvas = document.getElementById("graficoXYComparacion");
  if (!canvas) return;

  const ctx = canvas.getContext("2d");

  ctx.clearRect(0, 0, canvas.width, canvas.height);

  const padding = 55;
  const maxX = Math.max(risc.instrucciones, cisc.instrucciones, 1) + 2;
  const maxY = Math.max(risc.memoria, cisc.memoria, 1) + 2;

  function escalarX(x) {
    return padding + (x / maxX) * (canvas.width - padding * 2);
  }

  function escalarY(y) {
    return canvas.height - padding - (y / maxY) * (canvas.height - padding * 2);
  }

  ctx.strokeStyle = "#334155";
  ctx.lineWidth = 2;

  ctx.beginPath();
  ctx.moveTo(padding, padding);
  ctx.lineTo(padding, canvas.height - padding);
  ctx.lineTo(canvas.width - padding, canvas.height - padding);
  ctx.stroke();

  ctx.fillStyle = "#94a3b8";
  ctx.font = "13px Segoe UI";
  ctx.fillText("Accesos memoria", 15, 30);
  ctx.fillText("Instrucciones", canvas.width - 145, canvas.height - 18);

  ctx.strokeStyle = "#1e293b";
  ctx.lineWidth = 1;

  for (let i = 1; i <= maxX; i++) {
    const x = escalarX(i);
    ctx.beginPath();
    ctx.moveTo(x, padding);
    ctx.lineTo(x, canvas.height - padding);
    ctx.stroke();
  }

  for (let i = 1; i <= maxY; i++) {
    const y = escalarY(i);
    ctx.beginPath();
    ctx.moveTo(padding, y);
    ctx.lineTo(canvas.width - padding, y);
    ctx.stroke();
  }

  function punto(nombre, x, y, color) {
    const px = escalarX(x);
    const py = escalarY(y);

    ctx.beginPath();
    ctx.arc(px, py, 9, 0, Math.PI * 2);
    ctx.fillStyle = color;
    ctx.fill();

    ctx.fillStyle = "#e5e7eb";
    ctx.font = "14px Segoe UI";
    ctx.fillText(nombre, px + 14, py - 8);

    ctx.fillStyle = "#94a3b8";
    ctx.font = "12px Segoe UI";
    ctx.fillText(`(${x}, ${y})`, px + 14, py + 10);
  }

  punto("RISC", risc.instrucciones, risc.memoria, "#38bdf8");
  punto("CISC", cisc.instrucciones, cisc.memoria, "#22c55e");
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
  pintarCodigoComparacion();

  document.getElementById("conclusionComparacion").textContent =
    "Primero ejecuta los módulos RISC y CISC.";

  document.getElementById("resultadoComparacion").textContent =
    "No hay datos suficientes para comparar.";
}