const koa = require('koa');
const app = module.exports = new koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({ server });
const Router = require('koa-router');
const cors = require('@koa/cors');
const bodyParser = require('koa-bodyparser');

app.use(bodyParser());
app.use(cors());
app.use(middleware);

function middleware(ctx, next) {
  const start = new Date();
  return next().then(() => {
    const ms = new Date() - start;
    console.log(`${start.toLocaleTimeString()} ${ctx.response.status} ${ctx.request.method} ${ctx.request.url} - ${ms}ms`);
  });
}

const transactions = [
  { id: 1, date: '2025-01-15', amount: 150.75, type: 'expense', category: 'Groceries', description: 'Weekly grocery shopping' },
  { id: 2, date: '2025-01-16', amount: 2000.00, type: 'income', category: 'Salary', description: 'Monthly salary payment' },
  { id: 3, date: '2025-01-17', amount: 75.50, type: 'expense', category: 'Entertainment', description: 'Movie night' },
  { id: 4, date: '2025-01-18', amount: 300.00, type: 'expense', category: 'Rent', description: 'Monthly rent payment' },
  { id: 5, date: '2025-01-19', amount: 50.00, type: 'expense', category: 'Transport', description: 'Gas refill' },
  { id: 6, date: '2025-02-15', amount: 150.75, type: 'expense', category: 'Groceries', description: 'Weekly grocery shopping' },
  { id: 7, date: '2025-02-16', amount: 2000.00, type: 'income', category: 'Salary', description: 'Monthly salary payment' },
  { id: 8, date: '2025-02-17', amount: 75.50, type: 'expense', category: 'Entertainment', description: 'Movie night' },
  { id: 9, date: '2025-02-18', amount: 300.00, type: 'expense', category: 'Rent', description: 'Monthly rent payment' },
  { id: 10, date: '2025-02-19', amount: 50.00, type: 'expense', category: 'Transport', description: 'Gas refill' }
];

const router = new Router();

router.get('/transactions', ctx => {
  ctx.response.body = transactions;
  ctx.response.status = 200;
});

router.get('/transaction/:id', ctx => {
  const { id } = ctx.params;
  const transaction = transactions.find(t => t.id == id);
  if (transaction) {
    ctx.response.body = transaction;
    ctx.response.status = 200;
  } else {
    ctx.response.body = { error: `Transaction with id ${id} not found` };
    ctx.response.status = 404;
  }
});

router.post('/transaction', ctx => {
  const { date, amount, type, category, description } = ctx.request.body;

  if (date && amount && type && category && description) {
    const id = transactions.length > 0 ? Math.max(...transactions.map(t => t.id)) + 1 : 1;
    const newTransaction = { id, date, amount, type, category, description };
    transactions.push(newTransaction);

    broadcast(newTransaction);
    ctx.response.body = newTransaction;
    ctx.response.status = 201;
  } else {
    ctx.response.body = { error: "Missing or invalid transaction details" };
    ctx.response.status = 400;
  }
});

router.del('/transaction/:id', ctx => {
  const { id } = ctx.params;
  const index = transactions.findIndex(t => t.id == id);
  if (index !== -1) {
    const removedTransaction = transactions.splice(index, 1)[0];
    ctx.response.body = removedTransaction;
    ctx.response.status = 200;
  } else {
    ctx.response.body = { error: `Transaction with id ${id} not found` };
    ctx.response.status = 404;
  }
});

router.get('/allTransactions', ctx => {
  ctx.response.body = transactions;
  ctx.response.status = 200;
});

const broadcast = (data) => {
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });
};

app.use(router.routes());
app.use(router.allowedMethods());

const port = 2528;

server.listen(port, () => {
  console.log(`🚀 Server listening on ${port} ... 🚀`);
});
