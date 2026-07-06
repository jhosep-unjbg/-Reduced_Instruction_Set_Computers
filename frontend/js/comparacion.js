let comparacionInicializada = false;
let comparacionEjecutando = false;

function inicializarComparacion() {
  if (comparacionInicializada) return;
  comparacionInicializada = true;

  pintarCodigoComparacion();

  document
    .getElementById("btnAnalizarComparacion")
    ?.addEventListener("click", analizarComparacion);
}

function obtenerDatosComparacion() {
  return {
    A: Number(document.getElementById("inputA_Comparacion").value),
    B: Number(document.getElementById("inputB_Comparacion").value),
    C: Number(document.getElementById("inputC_Comparacion").value),
    D: Number(document.getElementById("inputD_Comparacion").value)
  };
}

async function analizarComparacion(event) {
  event?.preventDefault();

  if (comparacionEjecutando) return;

  const datos = obtenerDatosComparacion();
  comparacionEjecutando = true;

  const btn = document.getElementById("btnAnalizarComparacion");
  btn.disabled = true;
  btn.textContent = "Analizando...";

  const respuesta = await postData("/api/comparacion-risc-cisc", datos);

  if (!respuesta) {
    alert("No se pudo conectar con el backend.");
    finalizarComparacion();
    return;
  }

  pintarComparacion(respuesta, datos);
  finalizarComparacion();
}

function finalizarComparacion() {
  comparacionEjecutando = false;

  const btn = document.getElementById("btnAnalizarComparacion");
  if (btn) {
    btn.disabled = false;
    btn.textContent = "Analizar";
  }
}

function pintarComparacion(datos, entrada) {
  const risc = datos.risc;
  const cisc = datos.cisc;

  const registrosRisc = risc.registros ?? 8;
  const registrosCisc = cisc.registros ?? 2;
  const aluRisc = risc.alu ?? 3;
  const aluCisc = cisc.alu ?? 3;

  document.getElementById("cmpInstr").textContent =
    `${risc.instrucciones} vs ${cisc.instrucciones}`;

  document.getElementById("cmpMem").textContent =
    `${risc.memoria} vs ${cisc.memoria}`;

  document.getElementById("cmpPipe").textContent = "RISC";
  document.getElementById("cmpCodigo").textContent = "CISC";

  document.getElementById("txtRiscInstr").textContent = risc.instrucciones;
  document.getElementById("txtCiscInstr").textContent = cisc.instrucciones;

  document.getElementById("txtRiscMem").textContent = risc.memoria;
  document.getElementById("txtCiscMem").textContent = cisc.memoria;

  document.getElementById("tablaInstrRisc").textContent = risc.instrucciones;
  document.getElementById("tablaInstrCisc").textContent = cisc.instrucciones;
  document.getElementById("tablaMemRisc").textContent = risc.memoria;
  document.getElementById("tablaMemCisc").textContent = cisc.memoria;
  document.getElementById("tablaRegRisc").textContent = registrosRisc;
  document.getElementById("tablaRegCisc").textContent = registrosCisc;
  document.getElementById("tablaAluRisc").textContent = aluRisc;
  document.getElementById("tablaAluCisc").textContent = aluCisc;
  document.getElementById("tablaResultadoRisc").textContent = risc.resultado;
  document.getElementById("tablaResultadoCisc").textContent = cisc.resultado;

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

  const reduccionInstr = (
    ((risc.instrucciones - cisc.instrucciones) / risc.instrucciones) * 100
  ).toFixed(1);

  const ventajaPipeline = risc.pipeline - cisc.pipeline;
  const diferenciaComplejidad = cisc.complejidad - risc.complejidad;

  document.getElementById("conclusionComparacion").textContent =
    Number(risc.resultado) === Number(cisc.resultado)
      ? "Ambas arquitecturas producen el mismo resultado, pero con costos distintos."
      : "Los resultados no coinciden.";

  document.getElementById("resultadoComparacion").textContent =
    `Resultado: ${risc.resultado}. CISC reduce ${reduccionInstr}% de instrucciones. ` +
    `RISC tiene ${ventajaPipeline}% más compatibilidad con pipeline. ` +
    `CISC requiere ${diferenciaComplejidad}% más complejidad de hardware.`;

  dibujarGraficoXY(risc, cisc);
  pintarEjecucionDinamica(entrada);
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

function pintarEjecucionDinamica(datos) {
  const suma = datos.A + datos.B;
  const resta = datos.C - datos.D;
  const resultado = suma * resta;

  const pasos = [
    { paso: 1, operacion: "Cargar A", risc: datos.A, cisc: datos.A },
    { paso: 2, operacion: "A + B", risc: suma, cisc: suma },
    { paso: 3, operacion: "Cargar C", risc: datos.C, cisc: datos.C },
    { paso: 4, operacion: "C - D", risc: resta, cisc: resta },
    { paso: 5, operacion: "(A + B) × (C - D)", risc: resultado, cisc: resultado }
  ];

  const tabla = document.getElementById("tablaEjecucionComparacion");
  if (!tabla) return;

  tabla.innerHTML = "";

  pasos.forEach(p => {
    tabla.innerHTML += `
      <tr>
        <td>${p.paso}</td>
        <td>${p.operacion}</td>
        <td>${p.risc}</td>
        <td>${p.cisc}</td>
      </tr>
    `;
  });

  dibujarGraficoEjecucion(pasos);
}

function dibujarGraficoXY(risc, cisc) {
  const canvas = document.getElementById("graficoXYComparacion");
  if (!canvas) return;

  const ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  const padding = 55;
  const maxX = Math.max(risc.instrucciones, cisc.instrucciones, 1) + 2;
  const maxY = Math.max(risc.memoria, cisc.memoria, 1) + 2;

  const escalarX = x =>
    padding + (x / maxX) * (canvas.width - padding * 2);

  const escalarY = y =>
    canvas.height - padding - (y / maxY) * (canvas.height - padding * 2);

  dibujarEjes(ctx, canvas, padding, "Accesos memoria", "Instrucciones");

  dibujarPunto(ctx, escalarX(risc.instrucciones), escalarY(risc.memoria), "RISC", `(${risc.instrucciones}, ${risc.memoria})`, "#38bdf8");
  dibujarPunto(ctx, escalarX(cisc.instrucciones), escalarY(cisc.memoria), "CISC", `(${cisc.instrucciones}, ${cisc.memoria})`, "#22c55e");
}

function dibujarGraficoEjecucion(pasos) {
  const canvas = document.getElementById("graficoEjecucionComparacion");
  if (!canvas) return;

  const ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  const padding = 60;
  const valores = pasos.flatMap(p => [p.risc, p.cisc]);
  const minValor = Math.min(...valores, 0);
  const maxValor = Math.max(...valores, 1);

  const margen = Math.max(5, Math.abs(maxValor - minValor) * 0.15);
  const minY = minValor - margen;
  const maxY = maxValor + margen;

  const escalarX = index =>
    padding + (index / (pasos.length - 1)) * (canvas.width - padding * 2);

  const escalarY = valor =>
    canvas.height - padding -
    ((valor - minY) / (maxY - minY)) * (canvas.height - padding * 2);

  dibujarEjes(ctx, canvas, padding, "Valor calculado", "Paso");

  dibujarLinea(ctx, pasos.map((p, i) => ({
    x: escalarX(i),
    y: escalarY(p.risc),
    valor: p.risc,
    etiqueta: `P${p.paso}`
  })), "#38bdf8", "RISC");

  dibujarLinea(ctx, pasos.map((p, i) => ({
    x: escalarX(i),
    y: escalarY(p.cisc),
    valor: p.cisc,
    etiqueta: `P${p.paso}`
  })), "#22c55e", "CISC");
}

function dibujarEjes(ctx, canvas, padding, ejeY, ejeX) {
  ctx.strokeStyle = "#334155";
  ctx.lineWidth = 2;

  ctx.beginPath();
  ctx.moveTo(padding, padding);
  ctx.lineTo(padding, canvas.height - padding);
  ctx.lineTo(canvas.width - padding, canvas.height - padding);
  ctx.stroke();

  ctx.fillStyle = "#94a3b8";
  ctx.font = "13px Segoe UI";
  ctx.fillText(ejeY, 15, 30);
  ctx.fillText(ejeX, canvas.width - 90, canvas.height - 18);
}

function dibujarPunto(ctx, x, y, nombre, detalle, color) {
  ctx.beginPath();
  ctx.arc(x, y, 9, 0, Math.PI * 2);
  ctx.fillStyle = color;
  ctx.fill();

  ctx.fillStyle = "#e5e7eb";
  ctx.font = "14px Segoe UI";
  ctx.fillText(nombre, x + 14, y - 8);

  ctx.fillStyle = "#94a3b8";
  ctx.font = "12px Segoe UI";
  ctx.fillText(detalle, x + 14, y + 10);
}

function dibujarLinea(ctx, puntos, color, nombre) {
  ctx.strokeStyle = color;
  ctx.lineWidth = 3;

  ctx.beginPath();

  puntos.forEach((p, index) => {
    if (index === 0) ctx.moveTo(p.x, p.y);
    else ctx.lineTo(p.x, p.y);
  });

  ctx.stroke();

  puntos.forEach(p => {
    ctx.beginPath();
    ctx.arc(p.x, p.y, 7, 0, Math.PI * 2);
    ctx.fillStyle = color;
    ctx.fill();

    ctx.fillStyle = "#e5e7eb";
    ctx.font = "12px Segoe UI";
    ctx.fillText(String(p.valor), p.x + 8, p.y - 8);
    ctx.fillText(p.etiqueta, p.x - 8, p.y + 22);
  });

  const ultimo = puntos[puntos.length - 1];
  ctx.fillStyle = color;
  ctx.font = "14px Segoe UI";
  ctx.fillText(nombre, ultimo.x + 12, ultimo.y + 5);
}