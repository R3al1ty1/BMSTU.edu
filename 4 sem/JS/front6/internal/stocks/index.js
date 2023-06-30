const express = require('express');
const {StocksController} = require('./StocksController');

const router = express.Router();

router.get('/', StocksController.findStocks);
router.get('/find/:id', StocksController.findStockById);
router.post('/', StocksController.addStock);
router.delete('/delete/:id', StocksController.deleteStock);

module.exports = router;