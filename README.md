# Projeto RPC

Implementar uma agenda eletrônica, com as seguintes funcionalidades: insere, consulta, altera e remove. Utilize uma leitura e escrita no formato binário em arquivos texto, no servidor (para simular uma base de dados, sem a necessidade de instalar um SGBD) para armazenar os seguintes dados: nome, endereço, telefone. O campo chave para busca será o nome. As funcionalidades devem ser implementadas de forma remota, com o uso de RPC.


##### Considere as possíveis falhas em sistemas basados em RPC:
- Perda das mensagens de solicitação (mensagem enviada pelo cliente ao servidor), divido a problemas na rede;
- Perda das mensagens de resposta (mensagem enviada pelo servidor ao cliente), devido a problemas na rede.
- Sua implementação deve apresentar mecanismos (propostas de soluções) para tratar as falhas apresentadas acima.

