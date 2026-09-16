import net from 'net';

// Server Setting
const HOST = '127.0.0.1';
const PORT = 8888;

//Connection
const client = net.createConnection({ host: HOST, port: PORT }, () => {
  console.log(`✅ サーバーに接続しました: ${HOST}:${PORT}`);
  client.write('{"action_name": "select", "table":"temp","sql":"SELECT * FROM temp;"}');
});
// receive
client.on('data', (data) => {
  console.log('📩 受信データ:', data.toString());
  const rcv_data =  data.toString();
  const j1 = JSON.parse(rcv_data);
  console.log(j1.data)
});
client.on('end', () => {
  console.log('🔌 サーバーから切断されました');
});
// error
client.on('error', (err) => {
  console.error('❌ エラー:', err.message);
});
// Timeout
client.setTimeout(1000);
client.on('timeout', () => {
  console.log('⏰ タイムアウト');
  client.destroy();
});