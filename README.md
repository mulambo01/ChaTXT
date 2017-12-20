# ChatTXT

# Descrição:
Esse chat possui o proposito de garantir maior controle sobre conversas que precisam ser mantidas em sigilo. Para acessar o chat, todos os usuários devem estar dentro de um servidor rodando algum sistema GNU/Linux (creio que não surgirá grandes complicações em tentar colocá-lo num BSD). Basicamente, somente o root e o usuário "chatxt" possuirão permissão de leitura e escrita nos arquivos texto (chat.txt e pass.txt), o binário só poderá ser executado pelos membros do grupo "chatxt" e possuirá o SUID setado no usuário chatxt. Dessa forma, aqueles que o executarem estarão fazendo isso em nome do usuário chatxt podendo, assim, ler e escrever nos arquivos texto. Diferente do protocolo IRC, o qual acaba gerando um log em todos os clientes, o único log de conversa gerado ficará no próprio servidor podendo ser facilmente apagado em caso de emergência, além disso, graças ao fato de a rede local não ser usada para a trocação de mensagens, acaba se tornando mais complicado de haver algum logger no meio do caminho. É claro que toda segurança dependerá de uma série de outros fatores, como, por exemplo, o nível de vulnerabilidade do próprio servidor. Estudo a possibilidade de ser implementada alguma criptografia forte para que, mesmo com total controle sobre o server, o invasor não consiga ter acesso ao conteúdo da conversa. Para incrementar a segurança dos usuários, recomendo o uso da rede tor para o tunelamento dos dados trocados entre o user e o serviço SSH. Como o público será limitado, recomendo também o uso do método de autenticação por token no HiddenService.

# Dependências:
* libncurses-devel

# Instalação:
Inicialmente, você devera saciar todas as dependências citadas acima e o arquivo "compile.sh" deverá se tornar executável, para isso:

$ chmod +x compile.sh

Após executado como root, ele irá, automaticamente, configurar todo o ambiente realizando as seguintes tarefas:

* criar o usuário e o grupo de nome "chatxt"
* cria os arquivos chat.txt e pass.txt
* alterar a posse e as permissões dos arquivos
* compilar o programa

Após esse procedimento, todos os futuros usuários do chat deverão ser adicionados ao grupo "chatxt". Caso o script retorne algum erro, de uma olhada na fonte dele para pegar a ideia e realize o procedimento manualmente. É um script minúsculo, então não existe nenhum obstáculo para isso.

IMPORTANTE: quando testei no meu sistema (Slackware 14.2), possui um pequeno problema pois precisei reiniciar a sessão atual para que eu fosse reconhecido como membro do grupo.

# Pós instalação:
Não foi implementado nenhum procedimento para adicionar novos usuários, trocar senhas e demais tarefas de gerenciamento de contas. Decidi fazer assim porque esse tipo de complexidade desnecessária poderia gerar vulnerabilidades e comprometer áreas mais importantes do que a automatização de procedimentos. Dessa forma, cada usuário deverá rodar o script chamado "genpass.sh" escolher o nickname, a senha e passar a saída para o administrador do sistema que deverá adicionar a linha manualmente no arquivo pass.txt. A linha gerada irá conter o username associado a um hash simples da senha escolhida que basicamente será o md5 do md5 da senha (futuramente pretendo melhorar esse procedimento, por exemplo, adicionando um salt number).

# Uso:
São pouquissimos comandos existente no programa, antes de sabe-los é preciso entender algumas particularidades do mesmo. Visando a simplicidade representada pelo acrônimo KISS (Keep It Simple, Stupid) não é possível escrever e receber mensagens ao mesmo tempo. Dessa forma, quando o usuário aperta alguma tecla, o programa entra, de imediato, em modo de inserção, ficando surdo para quaisquer novas mensagens, após apertar enter, a mensagem será enviada e toda a janela do usuário será atualizada demarcando o ponto em que ele parou de receber o output. Existirão 2 modos de inserção, explicarei a particularidade de cada um abaixo:

1) Durante a implementação do modo rápido, acabei tendo um problema simples, pois os primeiros caracteres são os responsáveis por ativar a função que abre o modo de inserção e, por algum motivo obscuro, eles não podem ser apagados caso o usuário necessite de alterar o texto. Dessa forma, para cancelar o envio de uma mensagem, você deverá, simplesmente, acrescentar um # ao final da mensagem e dar enter.

2) Tendo em vista que o problema acima pode ser bem desconfortável nos momentos em que o texto é longo, o segundo método permite que o usuário edite a menságem normalmente. Para isso, basta apertar enter antes de digitar qualquer coisa e será exibida uma linha de input com o escrito: "MESSAGE:", dessa forma o usuário poderá escrever e apagar o texto tranquilamente, desde que não se quebre a linha.

Para sair do chat, basta digitar /quit e enviar.

feito por pixote.

Agradecimentos especiais ao srGaton.

A função geradora de md5 foi copiada de https://gist.github.com/creationix/4710780
