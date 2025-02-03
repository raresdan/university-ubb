const express = require('express')
const sqlite = require('sqlite3').verbose()
const websocket = require('ws')

const app = express();
const database = new sqlite.Database('articles.db')

app.use(express.json())

const wss = new websocket.Server({port: 3001})

wss.on('connection', (ws) => {
  console.log('Websocket new connection!')
})

function broadcastMessage(message) {
  wss.clients.forEach((client) => {
    if (client.readyState === websocket.OPEN)
      client.send(JSON.stringify(message))
  })
}

database.run(`
  CREATE TABLE IF NOT EXISTS articles(
      articleId INTEGER PRIMARY KEY AUTOINCREMENT,
      title TEXT NOT NULL,
      context TEXT NOT NULL,
      author TEXT NOT NULL,
      date TEXT NOT NULL,
      category TEXT NOT NULL);
`);

const PORT = 3000;


app.get('/articles', (req, res) => {
  console.log(`[GET /articles] Request received`);
  database.all('SELECT * FROM articles', [], (err, rows) => {
    if (err) {
      console.error(`[GET /articles] Error: ${err.message}`);
      res.status(500).json({ error: err.message });
    } else {
      console.log(`[GET /articles] Successfully retrieved ${rows.length} articles`);
      res.json(
        rows.map((article) => ({
          articleId: article.articleId,  
          title: article.title,
          context: article.context,
          author: article.author,
          date: new Date(article.date),
          category: article.category,
        }))
      );
    }
  });
});


app.post('/articles', (req, res) => {
  console.log(`[POST /articles] Request received with body:`, req.body);
  const { title, context, author, date, category } = req.body;

  database.run(
    'INSERT INTO articles (title, context, author, date, category) VALUES (?, ?, ?, ?, ?)',
    [title, context, author, date, category],
    function (err) {
      if (err) {
        console.error(`[POST /articles] Error: ${err.message}`);
        res.status(500).json({ error: err.message });
      } else {
        const newArticle = {
          articleId: this.lastID,
          title,
          context,
          author,
          date: new Date(),
          category,
        };
        console.log(`[POST /articles] Article added with ID: ${this.lastID}`);
        console.log(newArticle);

        broadcastMessage({type: 'add', payload: newArticle})

        res.json(newArticle);
      }
    }
  );
});


app.put('/articles/:id', (req, res) => {
  const { id } = req.params;
  console.log(`[PUT /articles/:id] Request received for ID: ${id} with body:`, req.body);
  const { title, context, author, date, category, articleId } = req.body;

  database.run(
    'UPDATE articles SET title = ?, context = ?, author = ?, date = ?, category = ? WHERE articleId = ?',
    [title, context, author, date, category, articleId],
    function (err) {
      if (err) {
        console.error(`[PUT /articles/:id] Error for ID ${id}: ${err.message}`);
        res.status(500).json({ error: err.message });
      } else {
        console.log(`[PUT /articles/:id] Task with ID ${id} updated. Changes: ${this.changes}`);
        const updatedArticle = {
          articleId: parseInt(id),
          title,
          context,
          author,
          date,
          category,
        };

        broadcastMessage({type: 'update', payload: updatedArticle})

        res.json(updatedArticle);
      }
    }
  );
});


app.delete('/articles/:id', (req, res) => {
  const { id } = req.params;
  console.log(`[DELETE /articles/:id] Request received for ID: ${id}`);

  database.run('DELETE FROM articles WHERE articleId = ?', [id], function (err) {
    if (err) {
      console.error(`[DELETE /articles/:id] Error for ID ${id}: ${err.message}`);
      res.status(500).json({ error: err.message });
    } else {
      console.log(`[DELETE /articles/:id] Article with ID ${id} deleted. Changes: ${this.changes}`);

      broadcastMessage({type: 'delete', payload: {articleId: parseInt(id)}})

      res.json({ changes: this.changes });
    }
  });
});



app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
  console.log(`WebSocket server running at ws://localhost:3001`);
});