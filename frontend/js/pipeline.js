let pipelineInicializado = false;
let pipelineEjecutando = false;
let pipelineTimers = [];

function inicializarPipeline() {
  if (pipelineInicializado) return;
  pipelineInicializado = true;

  const btn = document.getElementById("btnCalcularPipeline");
  if (!btn) return;

  btn.addEventListener("click", calcularPipeline);
}

async function calcularPipeline(event) {
  event?.preventDefault();

  if (pipelineEjecutando) return;

  const k = Number(document.getElementById("k").value);
  const n = Number(document.getElementById("n").value);
  const tau = Number(document.getElementById("tau").value);

  if (k <= 0 || n <= 0 || tau <= 0) {
    alert("Ingrese valores mayores que cero.");
    return;
  }

  detenerAnimacionPipeline();

  pipelineEjecutando = true;

  const btn = document.getElementById("btnCalcularPipeline");
  btn.disabled = true;
  btn.textContent = "Ejecutando...";

  const resultado = await postData("/api/pipeline", { k, n, tau });

  if (!resultado) {
    alert("No se pudo conectar con el backend Crow.");
    finalizarPipeline();
    return;
  }

  const ciclos = Number(resultado.ciclos);
  const tiempo = Number(resultado.tiempoTotal);
  const speedup = Number(resultado.speedup);
  const eficiencia = (speedup / k) * 100;

  actualizarResultadosPipeline(ciclos, tiempo, speedup, eficiencia);
  generarGanttPipeline(k, n);
  animarGanttPipeline(k, n);

  finalizarPipeline();
}

function finalizarPipeline() {
  pipelineEjecutando = false;

  const btn = document.getElementById("btnCalcularPipeline");
  if (btn) {
    btn.disabled = false;
    btn.textContent = "Calcular Pipeline";
  }
}

function actualizarResultadosPipeline(ciclos, tiempo, speedup, eficiencia) {
  document.getElementById("ciclos").textContent = ciclos + " ciclos";
  document.getElementById("tiempo").textContent = tiempo.toFixed(2) + " ns";
  document.getElementById("speedup").textContent = speedup.toFixed(2) + "x";
  document.getElementById("eficiencia").textContent = eficiencia.toFixed(2) + "%";

  document.getElementById("statCiclos").textContent = ciclos;
  document.getElementById("statTiempo").textContent = tiempo.toFixed(2) + " ns";
  document.getElementById("statSpeedup").textContent = speedup.toFixed(2) + "x";
  document.getElementById("statEficiencia").textContent = eficiencia.toFixed(1) + "%";
}

function generarGanttPipeline(k, n) {
  const etapasBase = ["IF", "ID", "EX", "MEM", "WB"];
  const etapas = [];

  for (let i = 0; i < k; i++) {
    etapas.push(etapasBase[i] || "E" + (i + 1));
  }

  const ciclosTotales = k + (n - 1);

  let html = "<table>";
  html += "<thead><tr><th>Instr.</th>";

  for (let c = 1; c <= ciclosTotales; c++) {
    html += `<th>C${c}</th>`;
  }

  html += "</tr></thead><tbody>";

  for (let i = 1; i <= n; i++) {
    html += `<tr><td>I${i}</td>`;

    for (let c = 1; c <= ciclosTotales; c++) {
      const etapaIndex = c - i;

      if (etapaIndex >= 0 && etapaIndex < k) {
        html += `
          <td>
            <span class="stage pipeline-cell" data-ciclo="${c}">
              ${etapas[etapaIndex]}
            </span>
          </td>`;
      } else {
        html += `<td class="empty-stage">-</td>`;
      }
    }

    html += "</tr>";
  }

  html += "</tbody></table>";

  document.getElementById("ganttPipeline").innerHTML = html;
}

function animarGanttPipeline(k, n) {
  const ciclosTotales = k + (n - 1);
  const velocidad = 500;

  for (let ciclo = 1; ciclo <= ciclosTotales; ciclo++) {
    const timer = setTimeout(() => {
      limpiarResaltadoPipeline();

      document
        .querySelectorAll(`.pipeline-cell[data-ciclo="${ciclo}"]`)
        .forEach(celda => celda.classList.add("stage-active"));

    }, ciclo * velocidad);

    pipelineTimers.push(timer);
  }
}

function detenerAnimacionPipeline() {
  pipelineTimers.forEach(timer => clearTimeout(timer));
  pipelineTimers = [];
  limpiarResaltadoPipeline();
}

function limpiarResaltadoPipeline() {
  document.querySelectorAll(".pipeline-cell").forEach(celda => {
    celda.classList.remove("stage-active");
  });
}