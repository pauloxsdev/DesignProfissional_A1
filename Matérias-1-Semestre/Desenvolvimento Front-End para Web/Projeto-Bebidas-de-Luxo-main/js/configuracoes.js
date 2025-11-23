// Coordenadas fictícias para a Cidade das Baladas
const cidadeDasBaladas = [-15.7801, -47.9292]; // Latitude e longitude fictícias (Brasília como exemplo)

// Inicializa o mapa e define o ponto central e o nível de zoom
// 'map' é o ID do elemento HTML onde o mapa será renderizado
const map = L.map('map').setView(cidadeDasBaladas, 13);

// Adiciona a camada base do mapa usando tiles do OpenStreetMap
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
  attribution: 'Mapa com Leaflet & OpenStreetMap', // Texto de atribuição
}).addTo(map);

// Cria um marcador no ponto definido
L.marker(cidadeDasBaladas)
  .addTo(map) // Adiciona o marcador ao mapa
  .bindPopup('<b>Rua Sem Número</b><br>Centro da Cidade das Baladas.') 
  .openPopup(); // Abre o popup automaticamente