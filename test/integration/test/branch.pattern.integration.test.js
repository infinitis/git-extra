const assert = require('assert');
const util = require('util');

const exec = util.promisify(require('child_process').exec);

const {reset_env,setup_env} = require('./utils.js');

describe('branch pattern integration test', () => {

	before(async() => {
		await reset_env();
		await setup_env();
	});

	it('should fail when given a branch pattern instead of the full branch', async() => {
		await assert.rejects(async() => await exec('git ex add -b mas* hello.txt',{cwd:"/home/node/working"}));
	});

});