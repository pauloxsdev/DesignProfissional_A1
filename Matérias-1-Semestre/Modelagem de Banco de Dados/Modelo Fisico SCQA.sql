CREATE TABLE Poluente (
    ID_Poluente integer PRIMARY KEY,
    Nome_Poluente varchar(100) NOT NULL,
    Formula_Quimica varchar(50)
);

CREATE TABLE Responsavel (
    ID_responsavel integer PRIMARY KEY,
    Nome varchar(100) NOT NULL,
    Email varchar(100) UNIQUE, -- Garante que não há emails duplicados
    Telefone varchar(20)
);

CREATE TABLE Estacao_de_Monitoramento (
    ID_estacao integer PRIMARY KEY,
    Nome varchar(100) NOT NULL,
    Latitude decimal(10, 7),
    Longitude decimal(10, 7),
    Endereco varchar(255),
    Status varchar(20) NOT NULL,
    
    ID_responsavel integer, 
    FOREIGN KEY (ID_responsavel) REFERENCES Responsavel(ID_responsavel)
);

CREATE TABLE Padrao_de_Qualidade (
    ID_Padrao integer PRIMARY KEY,
    Nivel_Qualidade decimal(10, 2) NOT NULL,
    Descricao_Efeitos varchar(255),
    ID_Poluente integer,
    
    FOREIGN KEY (ID_Poluente) REFERENCES Poluente(ID_Poluente)
);

CREATE TABLE Manutencao (
    ID_Manutencao integer PRIMARY KEY,
    Data_Inicio date NOT NULL,
    Data_Fim date,
    ID_Estacao integer,
    
    ID_responsavel integer, 
    
    FOREIGN KEY (ID_Estacao) REFERENCES Estacao_de_Monitoramento(ID_estacao),
    FOREIGN KEY (ID_responsavel) REFERENCES Responsavel(ID_responsavel)
);

CREATE TABLE Medicao (
    ID_Medicao integer PRIMARY KEY,
    Data date NOT NULL,
    Valor_Medido decimal(10, 3) NOT NULL,
    Unidade_Medida varchar(20),
    ID_Estacao integer,
    ID_Poluente integer,
    
    FOREIGN KEY (ID_Estacao) REFERENCES Estacao_de_Monitoramento(ID_estacao),
    FOREIGN KEY (ID_Poluente) REFERENCES Poluente(ID_Poluente)
);

CREATE TABLE Alerta (
    ID_Alerta integer PRIMARY KEY,
    Data date NOT NULL,
    Nivel_Alerta varchar(50),
    Status_Alerta varchar(50) NOT NULL,
    Descricao_Problema varchar(255),
    Descricao_Solucao varchar(255),
    Mensagem  varchar(255),
    ID_Medicao integer,
    
    FOREIGN KEY (ID_Medicao) REFERENCES Medicao(ID_Medicao)
);


INSERT INTO Poluente ( ID_Poluente, Nome_Poluente, Formula_Quimica ) VALUES ( 1, 'Dióxido de Carbono', 'CO2' );
INSERT INTO Poluente ( ID_Poluente, Nome_Poluente, Formula_Quimica ) VALUES ( 2, 'Dióxido de Enxofre', 'SO2' );
INSERT INTO Poluente ( ID_Poluente, Nome_Poluente, Formula_Quimica ) VALUES ( 3, 'Dióxido de Nitrogênio', 'NO2' );
INSERT INTO Poluente ( ID_Poluente, Nome_Poluente, Formula_Quimica ) VALUES ( 4, 'Ozônio', 'O3' );
INSERT INTO Poluente ( ID_Poluente, Nome_Poluente, Formula_Quimica ) VALUES ( 5, 'Material Particulado 2.5', 'PM2.5' );

INSERT INTO Responsavel ( ID_responsavel, Nome, Email, Telefone ) VALUES ( 1, 'Ana Silva', 'ana.silva@exemplo.com', '(11) 98765-4321' );
INSERT INTO Responsavel ( ID_responsavel, Nome, Email, Telefone ) VALUES ( 2, 'Bruno Costa', 'bruno.costa@exemplo.com', '(11) 98765-4322' );
INSERT INTO Responsavel ( ID_responsavel, Nome, Email, Telefone ) VALUES ( 3, 'Carla Dias', 'carla.dias@exemplo.com', '(11) 98765-4323' );
INSERT INTO Responsavel ( ID_responsavel, Nome, Email, Telefone ) VALUES ( 4, 'Daniel Moreira', 'daniel.moreira@exemplo.com', '(11) 98765-4324' );
INSERT INTO Responsavel ( ID_responsavel, Nome, Email, Telefone ) VALUES ( 5, 'Eliana Faria', 'eliana.faria@exemplo.com', '(11) 98765-4325' );

INSERT INTO Estacao_de_Monitoramento ( ID_estacao, Nome, Latitude, Longitude, Endereco, Status, ID_responsavel ) VALUES ( 1, 'Estação Centro', -23.550520, -46.633308, 'Praça da Sé, 100', 'Ativa', 1 );
INSERT INTO Estacao_de_Monitoramento ( ID_estacao, Nome, Latitude, Longitude, Endereco, Status, ID_responsavel ) VALUES ( 2, 'Estação Zona Norte', -23.509740, -46.623590, 'Av. Cruzeiro do Sul, 3000', 'Ativa', 2  );
INSERT INTO Estacao_de_Monitoramento ( ID_estacao, Nome, Latitude, Longitude, Endereco, Status, ID_responsavel ) VALUES ( 3, 'Estação Zona Sul', -23.601510, -46.660140, 'Av. Ibirapuera, 1500', 'Ativa', 1  );
INSERT INTO Estacao_de_Monitoramento ( ID_estacao, Nome, Latitude, Longitude, Endereco, Status, ID_responsavel ) VALUES ( 4, 'Estação Zona Leste', -23.541390, -46.471900, 'Rua da Mooca, 1200', 'Ativa', 3  );
INSERT INTO Estacao_de_Monitoramento ( ID_estacao, Nome, Latitude, Longitude, Endereco, Status, ID_responsavel ) VALUES ( 5, 'Estação Zona Oeste - Em Planejamento', NULL, NULL, NULL, 'Inativa', 4 );

INSERT INTO Padrao_de_Qualidade ( ID_Padrao, Nivel_Qualidade, Descricao_Efeitos, ID_Poluente ) VALUES ( 1, 400.00, 'Nível padrão de atenção para CO2', 1 );
INSERT INTO Padrao_de_Qualidade ( ID_Padrao, Nivel_Qualidade, Descricao_Efeitos, ID_Poluente ) VALUES ( 2, 20.00, 'Nível padrão OMS para SO2', 2 );
INSERT INTO Padrao_de_Qualidade ( ID_Padrao, Nivel_Qualidade, Descricao_Efeitos, ID_Poluente ) VALUES ( 3, 100.00, 'Nível padrão para NO2', 3 );
INSERT INTO Padrao_de_Qualidade ( ID_Padrao, Nivel_Qualidade, Descricao_Efeitos, ID_Poluente ) VALUES ( 4, 70.00, 'Nível padrão para Ozônio (O3)', 4 );
INSERT INTO Padrao_de_Qualidade ( ID_Padrao, Nivel_Qualidade, Descricao_Efeitos, ID_Poluente ) VALUES ( 5, 15.00, 'Nível padrão OMS para PM2.5', 5 );

INSERT INTO Manutencao ( ID_Manutencao, Data_Inicio, Data_Fim, ID_Estacao, ID_responsavel ) VALUES ( 1, '2025-10-01', '2025-10-02', 1, 1 );
INSERT INTO Manutencao ( ID_Manutencao, Data_Inicio, Data_Fim, ID_Estacao, ID_responsavel ) VALUES ( 2, '2025-10-15', '2025-10-15', 2, 2 );
INSERT INTO Manutencao ( ID_Manutencao, Data_Inicio, Data_Fim, ID_Estacao, ID_responsavel ) VALUES ( 3, '2025-11-05', '2025-11-05', 4, 3 );
INSERT INTO Manutencao ( ID_Manutencao, Data_Inicio, Data_Fim, ID_Estacao, ID_responsavel ) VALUES ( 4, '2025-11-12', '2025-11-13', 1, 4 );
INSERT INTO Manutencao ( ID_Manutencao, Data_Inicio, Data_Fim, ID_Estacao, ID_responsavel ) VALUES ( 5, '2025-11-13', NULL, 3, 5 );

INSERT INTO Medicao ( ID_Medicao, Data, Valor_Medido, Unidade_Medida, ID_Estacao, ID_Poluente ) VALUES ( 1, '2025-11-13', 450.500, 'ppm', 1, 1 );
INSERT INTO Medicao ( ID_Medicao, Data, Valor_Medido, Unidade_Medida, ID_Estacao, ID_Poluente ) VALUES ( 2, '2025-11-13', 25.000, 'µg/m³', 2, 2 );
INSERT INTO Medicao ( ID_Medicao, Data, Valor_Medido, Unidade_Medida, ID_Estacao, ID_Poluente ) VALUES ( 3, '2025-11-13', 105.000, 'µg/m³', 3, 3 );
INSERT INTO Medicao ( ID_Medicao, Data, Valor_Medido, Unidade_Medida, ID_Estacao, ID_Poluente ) VALUES ( 4, '2025-11-13', 17.500, 'µg/m³', 4, 5 );
INSERT INTO Medicao ( ID_Medicao, Data, Valor_Medido, Unidade_Medida, ID_Estacao, ID_Poluente ) VALUES ( 5, '2025-11-13', 75.000, 'µg/m³', 1, 4 );

INSERT INTO Alerta ( ID_Alerta, Data, Nivel_Alerta, Status_Alerta, Descricao_Problema, Descricao_Solucao, Mensagem, ID_Medicao ) VALUES ( 1, '2025-11-13', 'Alto', 'Ativo', 'Nível de CO2 excedeu 400ppm', NULL, 'Alerta Alto na Estação Centro', 1 );
INSERT INTO Alerta ( ID_Alerta, Data, Nivel_Alerta, Status_Alerta, Descricao_Problema, Descricao_Solucao, Mensagem, ID_Medicao ) VALUES ( 2, '2025-11-13', 'Médio', 'Ativo', 'Nível de SO2 excedeu 20ppm', NULL, 'Alerta Médio na Estação Zona Norte', 2 );
INSERT INTO Alerta ( ID_Alerta, Data, Nivel_Alerta, Status_Alerta, Descricao_Problema, Descricao_Solucao, Mensagem, ID_Medicao ) VALUES ( 3, '2025-11-13', 'Baixo', 'Resolvido', 'Nível de NO2 excedeu 100ppm', 'Variação normal, normalizado.', 'Alerta Baixo na Estação Zona Sul', 3 );
INSERT INTO Alerta ( ID_Alerta, Data, Nivel_Alerta, Status_Alerta, Descricao_Problema, Descricao_Solucao, Mensagem, ID_Medicao ) VALUES ( 4, '2025-11-13', 'Médio', 'Ativo', 'PM2.5 acima do padrão 15', NULL, 'Alerta Médio na Estação Zona Leste', 4 );
INSERT INTO Alerta ( ID_Alerta, Data, Nivel_Alerta, Status_Alerta, Descricao_Problema, Descricao_Solucao, Mensagem, ID_Medicao ) VALUES ( 5, '2025-11-13', 'Baixo', 'Resolvido', 'Nível de Ozônio excedeu 70ppm', 'Pico isolado, normalizado.', 'Alerta Baixo na Estação Centro', 5 );


select * from Poluente;
select * from Responsavel;
select * from Estacao_de_Monitoramento;
select * from Padrao_de_Qualidade;
select * from Manutencao;
select * from Medicao;
select * from Alerta;


-- Manipulação de Dados--

INSERT INTO Alerta ( ID_Alerta, Data, Nivel_Alerta, Status_Alerta, Descricao_Problema, Descricao_Solucao, Mensagem, ID_Medicao ) VALUES ( 6, '2025-11-14', 'Baixo', 'Ativo', 'Pico momentâneo de SO2', NULL, 'Alerta Baixo na Estação Zona Norte', 2 );

UPDATE Alerta 
SET Status_Alerta = 'Resolvido', Descricao_Solucao = 'Equipe enviada, sensor recalibrado.' 
WHERE ID_Alerta = 6;

DELETE FROM Alerta 
WHERE ID_Alerta = 6;