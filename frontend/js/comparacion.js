let comparacionInicializada = false;

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

  const datos = obtenerDatosComparacion();

  console.log("Datos enviados a comparación:", datos);

  const respuesta = await postData("/api/comparacion-risc-cisc", datos);

  console.log("Respuesta comparación:", respuesta);

  if (!respuesta) {
    alert("No se pudo conectar con el backend.");
    return;
  }

  pintarComparacion(respuesta, datos);
}

function pintarComparacion(datos, entrada) {
  const risc = datos.risc;
  const cisc = datos.cisc;

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

  document.getElementById("conclusionComparacion").textContent =
    Number(risc.resultado) === Number(cisc.resultado)
      ? "Ambas arquitecturas producen el mismo resultado."
      : "Los resultados no coinciden.";

  document.getElementById("resultadoComparacion").textContent =
    `Resultado con los datos ingresados: ${risc.resultado}`;
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
function pintarEjecucionDinamica(datos) {

    const suma = datos.A + datos.B;
    const resta = datos.C - datos.D;
    const resultado = suma * resta;

    const pasos = [
        { paso: 1, operacion: "Carga A", valor: datos.A },
        { paso: 2, operacion: "A + B", valor: suma },
        { paso: 3, operacion: "Carga C", valor: datos.C },
        { paso: 4, operacion: "C - D", valor: resta },
        { paso: 5, operacion: "Resultado", valor: resultado }
    ];

    const tabla = document.getElementById("tablaEjecucionComparacion");

    tabla.innerHTML = "";

    pasos.forEach(p => {

        tabla.innerHTML += `
        <tr>
            <td>${p.paso}</td>
            <td>${p.operacion}</td>
            <td>${p.valor}</td>
            <td>${p.valor}</td>
        </tr>
        `;

    });

    dibujarGraficoEjecucion(pasos);

}
function dibujarGraficoEjecucion(pasos){

    const canvas =
        document.getElementById("graficoEjecucionComparacion");

    if(!canvas) return;

    const ctx = canvas.getContext("2d");

    ctx.clearRect(0,0,canvas.width,canvas.height);

    const padding = 60;

    const max =
        Math.max(...pasos.map(p=>p.valor))+5;

    function X(i){

        return padding+
            (i/(pasos.length-1))*
            (canvas.width-padding*2);

    }

    function Y(v){

        return canvas.height-padding-
            (v/max)*
            (canvas.height-padding*2);

    }

    ctx.beginPath();

    pasos.forEach((p,i)=>{

        if(i===0)
            ctx.moveTo(X(i),Y(p.valor));
        else
            ctx.lineTo(X(i),Y(p.valor));

    });

    ctx.lineWidth=3;
    ctx.strokeStyle="#22c55e";
    ctx.stroke();

    pasos.forEach((p,i)=>{

        ctx.beginPath();
        ctx.arc(X(i),Y(p.valor),7,0,Math.PI*2);
        ctx.fillStyle="#38bdf8";
        ctx.fill();

        ctx.fillStyle="#fff";
        ctx.fillText(p.valor,X(i)+8,Y(p.valor)-8);

    });

}
