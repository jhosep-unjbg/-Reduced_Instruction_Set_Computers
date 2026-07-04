document.addEventListener("DOMContentLoaded", () => {
  const sidebarContainer = document.getElementById("sidebar-container");

  if (sidebarContainer) {
    fetch(getSidebarPath())
      .then(response => response.text())
      .then(html => {
        sidebarContainer.innerHTML = html;
        activarMenu();
      })
      .catch(error => {
        console.error("Error cargando sidebar:", error);
      });
  }
});

function getSidebarPath() {
  const isInsidePages = window.location.pathname.includes("/pages/");
  return isInsidePages ? "../components/sidebar.html" : "components/sidebar.html";
}

function activarMenu() {
  const currentPage = document.body.dataset.page;
  const links = document.querySelectorAll(".sidebar a");

  links.forEach(link => {
    if (link.dataset.page === currentPage) {
      link.classList.add("active");
    }
  });
}